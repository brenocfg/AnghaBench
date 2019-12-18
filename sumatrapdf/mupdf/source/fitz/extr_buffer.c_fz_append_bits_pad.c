#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_3__ {scalar_t__ unused_bits; } ;
typedef  TYPE_1__ fz_buffer ;

/* Variables and functions */

void
fz_append_bits_pad(fz_context *ctx, fz_buffer *buf)
{
	buf->unused_bits = 0;
}