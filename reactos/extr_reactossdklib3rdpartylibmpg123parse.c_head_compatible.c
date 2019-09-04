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
 unsigned long HDR_CMPMASK ; 
 scalar_t__ header_mono (unsigned long) ; 

__attribute__((used)) static int head_compatible(unsigned long fred, unsigned long bret)
{
	return ( (fred & HDR_CMPMASK) == (bret & HDR_CMPMASK)
		&&       header_mono(fred) == header_mono(bret)    );
}