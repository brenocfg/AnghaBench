#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  output; int /*<<< orphan*/  input; int /*<<< orphan*/  stream; int /*<<< orphan*/  stream_ended; } ;
typedef  TYPE_1__ ps_band_writer ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_band_writer ;

/* Variables and functions */
 int Z_OK ; 
 int deflateEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void
ps_drop_band_writer(fz_context *ctx, fz_band_writer *writer_)
{
	ps_band_writer *writer = (ps_band_writer *)writer_;

	if (!writer->stream_ended)
	{
		int err = deflateEnd(&writer->stream);
		if (err != Z_OK)
			fz_warn(ctx, "ignoring compression error %d", err);
	}

	fz_free(ctx, writer->input);
	fz_free(ctx, writer->output);
}