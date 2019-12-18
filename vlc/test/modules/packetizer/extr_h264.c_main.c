#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct params_s {int i_rate_num; int i_rate_den; int i_frame_count; int b_extra; int i_read_size; int /*<<< orphan*/  codec; int /*<<< orphan*/  obj; TYPE_1__* vlc; } ;
struct TYPE_4__ {int /*<<< orphan*/  p_libvlc_int; } ;
typedef  TYPE_1__ libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  RUN (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_CODEC_H264 ; 
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ ) ; 
 TYPE_1__* libvlc_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_release (TYPE_1__*) ; 
 int /*<<< orphan*/  test_init () ; 
 int /*<<< orphan*/  test_packetize ; 
 scalar_t__ test_samples_raw_h264 ; 
 scalar_t__ test_samples_raw_h264_len ; 

int main(void)
{
    test_init();

    libvlc_instance_t *vlc = libvlc_new(0, NULL);
    if(!vlc)
        return 1;

    struct params_s params;
    params.vlc = vlc;
    params.obj = VLC_OBJECT(vlc->p_libvlc_int);
    params.codec = VLC_CODEC_H264;
    params.i_rate_num = 0;
    params.i_rate_den = 0;
    params.i_frame_count = 2*25;
    params.b_extra = true;

    params.i_read_size = 500;
    RUN("block 500", test_packetize,
        test_samples_raw_h264, test_samples_raw_h264_len, 0);

    params.i_rate_num = 60000;
    params.i_rate_den = 1001;
    params.i_read_size = 8;
    RUN("block 8", test_packetize,
        test_samples_raw_h264, test_samples_raw_h264_len, 0);

    params.i_frame_count = 1*25;
    params.i_read_size = 500;
    RUN("skip 1st Iframe", test_packetize,
        test_samples_raw_h264 + 10, test_samples_raw_h264_len - 10, 0);

    libvlc_release(vlc);
    return 0;
}