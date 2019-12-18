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
struct TYPE_4__ {int /*<<< orphan*/  central; int /*<<< orphan*/  output; int /*<<< orphan*/  closed; } ;
typedef  TYPE_1__ fz_zip_writer ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_output (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 

void
fz_drop_zip_writer(fz_context *ctx, fz_zip_writer *zip)
{
	if (!zip)
		return;
	if (!zip->closed)
		fz_warn(ctx, "dropping unclosed zip writer");
	fz_drop_output(ctx, zip->output);
	fz_drop_buffer(ctx, zip->central);
	fz_free(ctx, zip);
}