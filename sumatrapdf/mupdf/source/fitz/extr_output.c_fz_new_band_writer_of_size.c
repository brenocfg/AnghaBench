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
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {int /*<<< orphan*/ * out; } ;
typedef  TYPE_1__ fz_band_writer ;

/* Variables and functions */
 TYPE_1__* fz_calloc (int /*<<< orphan*/ *,size_t,int) ; 

fz_band_writer *fz_new_band_writer_of_size(fz_context *ctx, size_t size, fz_output *out)
{
	fz_band_writer *writer = fz_calloc(ctx, size, 1);
	writer->out = out;
	return writer;
}