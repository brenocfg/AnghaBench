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
struct buffer {scalar_t__ size; scalar_t__ ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_reserve (struct buffer*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,int) ; 

__attribute__((used)) static inline void
write_bytes(struct buffer *b, const void * buf, int sz) {
	buffer_reserve(b,sz);
	memcpy(b->ptr + b->size, buf, sz);
	b->size += sz;
}