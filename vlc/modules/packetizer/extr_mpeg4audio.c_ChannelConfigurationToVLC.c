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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static int ChannelConfigurationToVLC(uint8_t i_channel)
{
    if (i_channel == 7)
        i_channel = 8; // 7.1
    else if (i_channel >= 8)
        i_channel = -1;
    return i_channel;
}