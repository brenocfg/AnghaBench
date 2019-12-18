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
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatalx (char*,...) ; 
 void* reallocarray (void*,size_t,size_t) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void *
xreallocarray(void *ptr, size_t nmemb, size_t size)
{
	void *new_ptr;

	if (nmemb == 0 || size == 0)
		fatalx("xreallocarray: zero size");
	new_ptr = reallocarray(ptr, nmemb, size);
	if (new_ptr == NULL)
		fatalx("xreallocarray: allocating %zu * %zu bytes: %s",
		    nmemb, size, strerror(errno));
	return new_ptr;
}