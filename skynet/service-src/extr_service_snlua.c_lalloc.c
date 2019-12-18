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
struct snlua {size_t mem; size_t mem_limit; size_t mem_report; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  skynet_error (int /*<<< orphan*/ ,char*,float) ; 
 void* skynet_lalloc (void*,size_t,size_t) ; 

__attribute__((used)) static void *
lalloc(void * ud, void *ptr, size_t osize, size_t nsize) {
	struct snlua *l = ud;
	size_t mem = l->mem;
	l->mem += nsize;
	if (ptr)
		l->mem -= osize;
	if (l->mem_limit != 0 && l->mem > l->mem_limit) {
		if (ptr == NULL || nsize > osize) {
			l->mem = mem;
			return NULL;
		}
	}
	if (l->mem > l->mem_report) {
		l->mem_report *= 2;
		skynet_error(l->ctx, "Memory warning %.2f M", (float)l->mem / (1024 * 1024));
	}
	return skynet_lalloc(ptr, osize, nsize);
}