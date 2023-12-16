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
     AVInputFormat *iformat =
        av_find_input_format("avfoundation");
    
    
    
    //3、打开音频设备
    
    AVFormatContext *fmt_ctx;//上下文
    char *deviceName=":0";
    
    AVDictionary *options = NULL;
    
    int ret=0;
    char errors[1024];
    
    if((ret=avformat_open_input(                        &fmt_ctx,
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
    
    while (rec_status) {
        ret=av_read_frame(fmt_ctx, &pkt);
        if(ret==-35) {
            usleep(20);//这个睡眠时间怎么定义呢？
            //sleep(1);
               continue;
        }
        
        if(ret<0){
            printf("read frame error ret=%d",ret);
            break;
        }
        
        printf("pkt size is %d \n",pkt.size);
        
        fwrite(pkt.data, pkt.size, 1, saveFile);
        
        av_packet_unref(&pkt);
    }
    
    
    //释放资源，防止内存泄露
    avformat_close_input(&fmt_ctx);//释放上下文
    fflush(saveFile);
    fclose(saveFile);
    
    printf("record over ret=%d",ret);
    
    
    
  
    
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


