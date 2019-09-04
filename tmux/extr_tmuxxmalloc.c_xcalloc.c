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
 void* calloc (size_t,size_t) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatalx (char*,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void *
xcalloc(size_t nmemb, size_t size)
{
	void *ptr;

	if (size == 0 || nmemb == 0)
		fatalx("xcalloc: zero size");
	ptr = calloc(nmemb, size);
	if (ptr == NULL)
		fatalx("xcalloc: allocating %zu * %zu bytes: %s",
		    nmemb, size, strerror(errno));
	return ptr;
}