//
//  ffmpeg_util.c
//  ffmpeg-demo2
//
//  Created by liuyongchang on 2023/12/6.
//

#include "ffmpeg_util.h"
void hello_ffmpeg(void){
    printf("Hello this form ffmpeg util\n");
    
    av_log_set_level(AV_LOG_DEBUG);
    av_log(NULL, AV_LOG_DEBUG, "ffmpeg 启动成功！日志成功了！！");
    
    return;
}
