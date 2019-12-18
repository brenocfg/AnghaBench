#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int i_sar_num; int i_sar_den; } ;
typedef  TYPE_1__ video_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_ureduce (int*,int*,int,int,int) ; 

void VoutFixFormatAR(video_format_t *fmt)
{
    vlc_ureduce( &fmt->i_sar_num, &fmt->i_sar_den,
                 fmt->i_sar_num,  fmt->i_sar_den, 50000 );
    if (fmt->i_sar_num <= 0 || fmt->i_sar_den <= 0) {
        fmt->i_sar_num = 1;
        fmt->i_sar_den = 1;
    }
}