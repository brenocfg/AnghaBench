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
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_tick_from_sec (int const) ; 

__attribute__((used)) static vlc_tick_t ParseTimeCode(const uint8_t *data, double fps)
{
    return vlc_tick_from_sec( data[0] * 3600 +
                         data[1] *   60 +
                         data[2] *    1 +
                         data[3] /  fps);
}