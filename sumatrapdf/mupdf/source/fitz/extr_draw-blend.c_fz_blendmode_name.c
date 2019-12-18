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
 scalar_t__* fz_blendmode_names ; 
 scalar_t__ nelem (scalar_t__*) ; 

char *fz_blendmode_name(int blendmode)
{
	if (blendmode >= 0 && blendmode < (int)nelem(fz_blendmode_names))
		return (char*)fz_blendmode_names[blendmode];
	return "Normal";
}