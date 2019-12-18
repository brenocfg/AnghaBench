#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int def_count; int /*<<< orphan*/ * out; TYPE_1__* defs_buffer; int /*<<< orphan*/ * out_store; } ;
typedef  TYPE_2__ svg_device ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {scalar_t__ len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  fz_write_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static fz_output *
end_def(fz_context *ctx, svg_device *sdev)
{
	if (sdev->def_count > 0)
		sdev->def_count--;
	if (sdev->def_count == 1)
		sdev->out = sdev->out_store;
	if (sdev->def_count == 0 && sdev->defs_buffer != NULL)
	{
		fz_write_data(ctx, sdev->out, sdev->defs_buffer->data, sdev->defs_buffer->len);
		sdev->defs_buffer->len = 0;
	}
	return sdev->out;
}