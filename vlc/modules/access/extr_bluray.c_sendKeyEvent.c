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
struct TYPE_3__ {int /*<<< orphan*/  bluray; } ;
typedef  TYPE_1__ demux_sys_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ bd_user_input (int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int sendKeyEvent(demux_sys_t *p_sys, unsigned int key)
{
    if (bd_user_input(p_sys->bluray, -1, key) < 0)
        return VLC_EGENERIC;

    return VLC_SUCCESS;
}