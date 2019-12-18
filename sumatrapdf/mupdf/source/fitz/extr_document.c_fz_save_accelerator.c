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
struct TYPE_4__ {int /*<<< orphan*/ * output_accelerator; } ;
typedef  TYPE_1__ fz_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_new_output_with_path (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_output_accelerator (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

void fz_save_accelerator(fz_context *ctx, fz_document *doc, const char *accel)
{
	if (doc == NULL)
		return;
	if (doc->output_accelerator == NULL)
		return;

	fz_output_accelerator(ctx, doc, fz_new_output_with_path(ctx, accel, 0));
}