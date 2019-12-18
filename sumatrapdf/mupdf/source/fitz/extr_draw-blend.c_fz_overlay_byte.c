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
 int fz_hard_light_byte (int,int) ; 

__attribute__((used)) static inline int fz_overlay_byte(int b, int s)
{
	return fz_hard_light_byte(s, b); /* note swapped order */
}