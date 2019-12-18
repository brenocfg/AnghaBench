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

/* Variables and functions */
 scalar_t__ TTYM_SGR ; 
 scalar_t__ TTYM_URXVT ; 
 scalar_t__ TTYM_XTERM ; 
 scalar_t__ TTYM_XTERM2 ; 
 scalar_t__ ttym_flags ; 

int
use_xterm_mouse()
{
    if (ttym_flags == TTYM_SGR)
	return 4;
    if (ttym_flags == TTYM_URXVT)
	return 3;
    if (ttym_flags == TTYM_XTERM2)
	return 2;
    if (ttym_flags == TTYM_XTERM)
	return 1;
    return 0;
}