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
struct _malloc_zone_t {int dummy; } ;

/* Variables and functions */
 void* je_malloc (size_t) ; 

__attribute__((used)) static unsigned
zone_batch_malloc(struct _malloc_zone_t *zone, size_t size, void **results,
    unsigned num_requested) {
	unsigned i;

	for (i = 0; i < num_requested; i++) {
		results[i] = je_malloc(size);
		if (!results[i])
			break;
	}

	return i;
}