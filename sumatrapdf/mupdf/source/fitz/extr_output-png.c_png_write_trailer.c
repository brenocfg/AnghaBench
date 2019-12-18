#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * out; } ;
struct TYPE_4__ {int stream_ended; int /*<<< orphan*/  stream; TYPE_1__ super; } ;
typedef  TYPE_2__ png_band_writer ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_band_writer ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int Z_OK ; 
 int deflateEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  putchunk (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
png_write_trailer(fz_context *ctx, fz_band_writer *writer_)
{
	png_band_writer *writer = (png_band_writer *)(void *)writer_;
	fz_output *out = writer->super.out;
	unsigned char block[1];
	int err;

	writer->stream_ended = 1;
	err = deflateEnd(&writer->stream);
	if (err != Z_OK)
		fz_throw(ctx, FZ_ERROR_GENERIC, "compression error %d", err);

	putchunk(ctx, out, "IEND", block, 0);
}