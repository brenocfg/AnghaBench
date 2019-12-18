#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {size_t len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ fz_buffer ;

/* Variables and functions */
 TYPE_1__* fz_new_buffer (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,size_t) ; 

fz_buffer *
fz_new_buffer_from_copied_data(fz_context *ctx, const unsigned char *data, size_t size)
{
	fz_buffer *b = fz_new_buffer(ctx, size);
	b->len = size;
	memcpy(b->data, data, size);
	return b;
}