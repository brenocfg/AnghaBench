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
struct TYPE_3__ {int size; int base_size; int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * scratch; scalar_t__ len; } ;
typedef  TYPE_1__ pdf_lexbuf ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

void pdf_lexbuf_init(fz_context *ctx, pdf_lexbuf *lb, int size)
{
	lb->size = lb->base_size = size;
	lb->len = 0;
	lb->scratch = &lb->buffer[0];
}