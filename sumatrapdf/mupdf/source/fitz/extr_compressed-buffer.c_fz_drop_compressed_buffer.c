#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_7__ {int /*<<< orphan*/  globals; } ;
struct TYPE_8__ {TYPE_1__ jbig2; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_2__ u; } ;
struct TYPE_10__ {int /*<<< orphan*/  buffer; TYPE_3__ params; } ;
typedef  TYPE_4__ fz_compressed_buffer ;

/* Variables and functions */
 scalar_t__ FZ_IMAGE_JBIG2 ; 
 int /*<<< orphan*/  fz_drop_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_jbig2_globals (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_4__*) ; 

void
fz_drop_compressed_buffer(fz_context *ctx, fz_compressed_buffer *buf)
{
	if (buf)
	{
		if (buf->params.type == FZ_IMAGE_JBIG2)
			fz_drop_jbig2_globals(ctx, buf->params.u.jbig2.globals);
		fz_drop_buffer(ctx, buf->buffer);
		fz_free(ctx, buf);
	}
}