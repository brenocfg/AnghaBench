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
struct bson {scalar_t__ ptr; scalar_t__ buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 

__attribute__((used)) static inline void
bson_destroy(struct bson *b) {
	if (b->ptr != b->buffer) {
		free(b->ptr);
	}
}