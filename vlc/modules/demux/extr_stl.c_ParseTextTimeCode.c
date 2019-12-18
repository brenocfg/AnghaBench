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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  ParseInteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ParseTimeCode (int /*<<< orphan*/ *,double) ; 

__attribute__((used)) static vlc_tick_t ParseTextTimeCode(uint8_t *data, double fps)
{
    uint8_t tmp[4];
    for (int i = 0; i < 4; i++)
        tmp[i] = ParseInteger(&data[2 * i], 2);
    return ParseTimeCode(tmp, fps);
}