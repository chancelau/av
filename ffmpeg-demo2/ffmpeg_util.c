//
//  ffmpeg_util.c
//  ffmpeg-demo2
//
//  Created by liuyongchang on 2023/12/6.

//  代码风格，所有变量定义在函数的前面
//

#include "ffmpeg_util.h"


static int rec_status=0;


void set_status(int status){
    rec_status = status;
}

void rec_audio(void){
    //打开音频设备
    //1、注册设备
    avdevice_register_all();
    
    
    //2、设置采集方式（avfoundation/dshow/alsa）
     AVInputFormat *iformat =av_find_input_format("avfoundation");
    
    
    
    //3、打开音频设备
    
    AVFormatContext *fmt_ctx;//上下文
    char *deviceName=":0";
    
    AVDictionary *options = NULL;
    
    int ret=0;
    char errors[1024];
    
    if((ret=avformat_open_input(                        
                                &fmt_ctx,
                        deviceName,
                        iformat,
                                &options))<0){
        av_strerror(ret, errors, 1024);
        printf(stderr,"Faild to open device,[%d]：%s\n",ret,errors);
            
                                    return;
     }
    
    //读取数据
    printf("设备打开成功，即将读取数据\n");
    
    AVPacket pkt;
    av_init_packet(&pkt);
    int count=0;
    sleep(1);
    
    //文件定义
    char savePath[100];
    char currentTimeStr[50];
    get_current_time_str(currentTimeStr, 50);
    snprintf(savePath, sizeof(savePath), "/Users/lyc/Downloads/%s.pcm", currentTimeStr);
    
    FILE* saveFile = fopen(savePath, "wb+");
    
    
    //重采样上下文
    SwrContext *swr_ctx=NULL;


    swr_ctx=swr_alloc_set_opts(
                      NULL,//上下文，入参
                       AV_CH_LAYOUT_STEREO,//输出 channel布局，立体声
                       AV_SAMPLE_FMT_S16,//输出采用格式
                       44100,//采样率
                       AV_CH_LAYOUT_STEREO,//输入 channle 布局
                       AV_SAMPLE_FMT_FLT,//输入的采样格式
                       44100,//输入采样率
                       0, NULL);

//    int ret2 = swr_alloc_set_opts2(&swr_ctx,         // we're allocating a new context
//                          &(AVChannelLayout)AV_CHANNEL_LAYOUT_STEREO, // out_ch_layout
//                          AV_SAMPLE_FMT_S16,    // out_sample_fmt
//                          44100,                // out_sample_rate
//                          &(AVChannelLayout)AV_CHANNEL_LAYOUT_5POINT1, // in_ch_layout
//                          AV_SAMPLE_FMT_FLTP,   // in_sample_fmt
//                          48000,                // in_sample_rate
//                          0,                    // log_offset
//                          NULL);                // log_ctx
    
    if (swr_ctx == NULL) {
        printf("创建重采样上下文失败");
        return;
    }
    
    if (swr_init(swr_ctx)<0) {
        printf("初始化重采样上下文失败");
        return;
    }
    
//
    uint8_t **src_data;
    int src_linesize=0;
    
    uint8_t **dst_data;
    int dst_linesize=0;
    
    //创建输入缓冲区
    av_samples_alloc_array_and_samples(&src_data,//输出缓冲区地址
                                        &src_linesize,//缓冲区大小
                                        1,//通道个数
                                        512,//采样数,单个通道采样数据=采集数据/4/2
                                        AV_SAMPLE_FMT_FLT,//采样格式
                                       0);

    //创建输出缓冲区
    av_samples_alloc_array_and_samples(&dst_data,//输入缓冲区地址
                                        &dst_linesize,//缓冲区大小
                                        1,//通道个数
                                       512,//采样数,单个通道采样数据=采集数据/4/2
                                       AV_SAMPLE_FMT_S16,//采样格式
                                       0);
    
      
    while (rec_status) {
        ret=av_read_frame(fmt_ctx, &pkt);
        if(ret==-35) {
            usleep(20);//这个睡眠时间怎么定义呢？
    
               continue;
        }
        
        if(ret<0){
            printf("read frame error ret=%d",ret);
            break;
        }
        
        av_log(NULL, AV_LOG_INFO,
               "ret=%d,packet size is %d(%p)\n",
              ret, pkt.size, pkt.data);
        
        
//        //内存拷贝，按照字节拷贝，将pkt.data 拷贝到srcdata中
        memcpy((void*)src_data[0], (void*)pkt.data, pkt.size);
//
//        //重采样
//        //pkt data 中的数据不满足 out,in 中双指针的格式
        
        swr_convert(swr_ctx,
                    dst_data,
                    512,
                    (const uint8_t **)src_data,
                    512);
        
        printf("pkt size is %d（%p） \n",pkt.size,pkt.data);
//        fwrite(pkt.data, pkt.size, 1, saveFile);//PCM数据保存
        //if(sizeof(dst_data)>0)
        fwrite(dst_data[0],1,dst_linesize, saveFile);
        fflush(saveFile);
        
        av_packet_unref(&pkt);
    
    }
    
    printf("record over ret=%d \n",ret);
    //释放资源，防止内存泄露
    avformat_close_input(&fmt_ctx);
 
    fclose(saveFile);
    
    
    
    
    
    if(src_data){
        av_freep(&src_data[0]);
    }
    
    av_freep(src_data);
   
    
    
    if(dst_data){
        av_freep(&dst_data[0]);
    }
    
    av_freep(dst_data);
    
    swr_free(&swr_ctx);
    avformat_close_input(&fmt_ctx);//释放上下文

   
    
 
    
    av_log(NULL, AV_LOG_DEBUG, "record finish!!");
  
    
    return;
}




void get_current_time_str(char *currentTimeString, int bufferSize) {
    time_t currentTime;
    struct tm *localTime;

    // 获取当前时间的秒数
    time(&currentTime);

    // 将时间转换为本地时间结构体
    localTime = localtime(&currentTime);

    // 格式化当前时间为字符串
    strftime(currentTimeString, bufferSize, "%Y%m%d%H%M%S", localTime);
    
}


