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
typedef  int /*<<< orphan*/  uint8_t ;
struct bson {int /*<<< orphan*/  size; int /*<<< orphan*/ * ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  bson_reserve (struct bson*,int) ; 

__attribute__((used)) static inline void
write_byte(struct bson *b, uint8_t v) {
	bson_reserve(b,1);
	b->ptr[b->size++] = v;
}