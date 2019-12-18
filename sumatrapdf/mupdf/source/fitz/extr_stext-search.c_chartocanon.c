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
 int canon (int) ; 
 int fz_chartorune (int*,char const*) ; 

__attribute__((used)) static inline int chartocanon(int *c, const char *s)
{
	int n = fz_chartorune(c, s);
	*c = canon(*c);
	return n;
}