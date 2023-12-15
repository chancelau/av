//
//  ffmpeg_util.h
//  ffmpeg-demo2
//
//  Created by liuyongchang on 2023/12/6.
//

#ifndef ffmpeg_util_h
#define ffmpeg_util_h

#include <stdio.h>
#include "libavutil/avutil.h"
#include "libavdevice/avdevice.h"//负责设备
#include "libavformat/avformat.h" // 负责格式（同意解析格式）
#include "libavcodec/avcodec.h"// 音频采集
#include "unistd.h"//睡眠
#include "time.h"
#include "string.h"

void rec_audio(void);
void set_status(int status);
void get_current_time_str(char *currentTimeString, int bufferSize) ;



#endif /* ffmpeg_util_h */
