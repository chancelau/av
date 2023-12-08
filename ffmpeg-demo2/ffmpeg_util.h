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
#include "libavformat/avformat.h" // 负责格式

void hello_ffmpeg(void);

#endif /* ffmpeg_util_h */
