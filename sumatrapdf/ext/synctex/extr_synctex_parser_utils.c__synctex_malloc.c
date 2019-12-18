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
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

void *_synctex_malloc(size_t size) {
	void * ptr = malloc(size);
	if(ptr) {
/*  There used to be a switch to use bzero because it is more secure. JL */
		memset(ptr,0, size);
	}
	return (void *)ptr;
}