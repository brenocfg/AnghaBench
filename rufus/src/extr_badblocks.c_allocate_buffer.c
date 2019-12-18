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
 int /*<<< orphan*/  BB_SYS_PAGE_SIZE ; 
 void* _mm_malloc (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void *allocate_buffer(size_t size) {
	return _mm_malloc(size, BB_SYS_PAGE_SIZE);
}