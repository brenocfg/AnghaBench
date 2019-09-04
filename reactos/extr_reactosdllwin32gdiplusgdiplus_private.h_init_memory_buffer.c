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
struct memory_buffer {scalar_t__ pos; int /*<<< orphan*/  size; int /*<<< orphan*/  const* buffer; } ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */

__attribute__((used)) static inline void init_memory_buffer(struct memory_buffer *mbuf, const BYTE *buffer, INT size)
{
    mbuf->buffer = buffer;
    mbuf->size = size;
    mbuf->pos = 0;
}