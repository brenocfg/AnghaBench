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
struct cidrange {unsigned int lo; } ;

/* Variables and functions */

__attribute__((used)) static int cmpcidrange(const void *va, const void *vb)
{
	unsigned int a = ((const struct cidrange *)va)->lo;
	unsigned int b = ((const struct cidrange *)vb)->lo;
	return a < b ? -1 : a > b ? 1 : 0;
}