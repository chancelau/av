//
//  ffmpeg_util.c
//  ffmpeg-demo2
//
//  Created by liuyongchang on 2023/12/6.
//

#include "ffmpeg_util.h"
void hello_ffmpeg(void){
    printf("Hello this form ffmpeg util\n");
    
    AVFormatContext *fmt_ctx  = NULL;
    
    AVDictionary *options = NULL;
    
    int ret = 0;
    char errors[1024];
    
    //[[video device]:[audio device]]
    char *devicename = ":0";
    
    
    av_log_set_level(AV_LOG_DEBUG);
    av_log(NULL, AV_LOG_DEBUG, "ffmpeg 启动成功！日志成功了！！");
    
    //register audio device
    avdevice_register_all();
    
    //get format
    AVInputFormat *iformat = av_find_input_format("avfoundation");
    
    
    ret = avformat_open_input(&fmt_ctx,
                        devicename,
                        iformat,
                        &options);
    
    if(ret<0){
        av_strerror(ret, errors, 1024);
        printf(stderr,"Failed to open audio device,[%d]%s\n",ret,errors); 
    }else{
        printf(stdout,"设备打开成功！");
    }
    
    return;
}
