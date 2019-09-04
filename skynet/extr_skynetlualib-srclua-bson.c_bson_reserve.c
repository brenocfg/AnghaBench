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
struct bson {int size; int cap; scalar_t__ ptr; scalar_t__ buffer; } ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 scalar_t__ realloc (scalar_t__,int) ; 

__attribute__((used)) static inline void
bson_reserve(struct bson *b, int sz) {
	if (b->size + sz <= b->cap)
		return;
	do {
		b->cap *= 2;
	} while (b->cap <= b->size + sz);

	if (b->ptr == b->buffer) {
		b->ptr = malloc(b->cap);
		memcpy(b->ptr, b->buffer, b->size);
	} else {
		b->ptr = realloc(b->ptr, b->cap);
	}
}