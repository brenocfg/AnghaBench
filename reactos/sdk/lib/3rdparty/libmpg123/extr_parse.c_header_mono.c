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
 int FALSE ; 
 scalar_t__ HDR_CHANNEL_VAL (unsigned long) ; 
 scalar_t__ MPG_MD_MONO ; 
 int TRUE ; 

__attribute__((used)) static int header_mono(unsigned long newhead)
{
	return HDR_CHANNEL_VAL(newhead) == MPG_MD_MONO ? TRUE : FALSE;
}