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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  ToxAV ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,int) ; 

void t_toxav_bit_rate_status_cb(ToxAV *av, uint32_t friend_number,
                                uint32_t audio_bit_rate, uint32_t video_bit_rate,
                                void *user_data)
{
    printf ("Suggested bit rates: audio: %d video: %d\n", audio_bit_rate, video_bit_rate);
}