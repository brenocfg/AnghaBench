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
 int jsM_rand_temper (unsigned int) ; 

__attribute__((used)) static int jsM_rand_r(unsigned int *seed)
{
	return jsM_rand_temper(*seed = *seed * 1103515245 + 12345)/2;
}