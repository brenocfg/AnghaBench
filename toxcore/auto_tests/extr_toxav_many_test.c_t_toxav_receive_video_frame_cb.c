#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  ToxAV ;

/* Variables and functions */

void t_toxav_receive_video_frame_cb(ToxAV *av, uint32_t friend_number,
                                    uint16_t width, uint16_t height,
                                    uint8_t const *y, uint8_t const *u, uint8_t const *v,
                                    int32_t ystride, int32_t ustride, int32_t vstride,
                                    void *user_data)
{
    (void) av;
    (void) friend_number;
    (void) width;
    (void) height;
    (void) y;
    (void) u;
    (void) v;
    (void) ystride;
    (void) ustride;
    (void) vstride;
    (void) user_data;
}