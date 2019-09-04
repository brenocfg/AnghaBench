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
typedef  int uint32_t ;
struct buffer {int* ptr; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */

__attribute__((used)) static inline void
write_length(struct buffer *b, int32_t v, int off) {
	uint32_t uv = (uint32_t)v;
	b->ptr[off++] = uv & 0xff;
	b->ptr[off++] = (uv >> 8)&0xff;
	b->ptr[off++] = (uv >> 16)&0xff;
	b->ptr[off++] = (uv >> 24)&0xff;
}