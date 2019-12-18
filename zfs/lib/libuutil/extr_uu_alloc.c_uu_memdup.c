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
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 void* uu_zalloc (size_t) ; 

void *
uu_memdup(const void *buf, size_t sz)
{
	void *p;

	p = uu_zalloc(sz);
	if (p == NULL)
		return (NULL);
	(void) memcpy(p, buf, sz);
	return (p);
}