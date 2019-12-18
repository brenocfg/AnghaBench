#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uInt ;
struct TYPE_7__ {scalar_t__ avail_out; void* next_out; void* avail_in; int /*<<< orphan*/ * next_in; int /*<<< orphan*/  zfree; int /*<<< orphan*/  zalloc; int /*<<< orphan*/ * opaque; } ;
struct TYPE_5__ {int w; int h; int n; scalar_t__ alpha; int /*<<< orphan*/ * out; } ;
struct TYPE_6__ {unsigned char* udata; int usize; int csize; void* cdata; TYPE_3__ stream; TYPE_1__ super; } ;
typedef  TYPE_2__ png_band_writer ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_band_writer ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int FZ_MAX_COLORS ; 
 int /*<<< orphan*/  Z_DEFAULT_COMPRESSION ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int compressBound (int) ; 
 int deflate (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int deflateInit (TYPE_3__*,int /*<<< orphan*/ ) ; 
 void* fz_malloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fz_zlib_alloc ; 
 int /*<<< orphan*/  fz_zlib_free ; 
 int /*<<< orphan*/  putchunk (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,void*,int) ; 

__attribute__((used)) static void
png_write_band(fz_context *ctx, fz_band_writer *writer_, int stride, int band_start, int band_height, const unsigned char *sp)
{
	png_band_writer *writer = (png_band_writer *)(void *)writer_;
	fz_output *out = writer->super.out;
	unsigned char *dp;
	int y, x, k, err, finalband;
	int w, h, n;

	if (!out)
		return;

	w = writer->super.w;
	h = writer->super.h;
	n = writer->super.n;

	finalband = (band_start+band_height >= h);
	if (finalband)
		band_height = h - band_start;

	if (writer->udata == NULL)
	{
		writer->usize = (w * n + 1) * band_height;
		/* Sadly the bound returned by compressBound is just for a
		 * single usize chunk; if you compress a sequence of them
		 * the buffering can result in you suddenly getting a block
		 * larger than compressBound outputted in one go, even if you
		 * take all the data out each time. */
		writer->csize = compressBound(writer->usize);
		writer->udata = fz_malloc(ctx, writer->usize);
		writer->cdata = fz_malloc(ctx, writer->csize);
		writer->stream.opaque = ctx;
		writer->stream.zalloc = fz_zlib_alloc;
		writer->stream.zfree = fz_zlib_free;
		err = deflateInit(&writer->stream, Z_DEFAULT_COMPRESSION);
		if (err != Z_OK)
			fz_throw(ctx, FZ_ERROR_GENERIC, "compression error %d", err);
	}

	dp = writer->udata;
	stride -= w*n;
	if (writer->super.alpha)
	{
		/* Unpremultiply data */
		for (y = 0; y < band_height; y++)
		{
			int prev[FZ_MAX_COLORS];
			*dp++ = 1; /* sub prediction filter */
			for (x = 0; x < w; x++)
			{
				int a = sp[n-1];
				int inva = a ? 256*255/a : 0;
				int p;
				for (k = 0; k < n-1; k++)
				{
					int v = (sp[k] * inva + 128)>>8;
					p = x ? prev[k] : 0;
					prev[k] = v;
					v -= p;
					dp[k] = v;
				}
				p = x ? prev[k] : 0;
				prev[k] = a;
				a -= p;
				dp[k] = a;
				sp += n;
				dp += n;
			}
			sp += stride;
		}
	}
	else
	{
		for (y = 0; y < band_height; y++)
		{
			*dp++ = 1; /* sub prediction filter */
			for (x = 0; x < w; x++)
			{
				for (k = 0; k < n; k++)
				{
					if (x == 0)
						dp[k] = sp[k];
					else
						dp[k] = sp[k] - sp[k-n];
				}
				sp += n;
				dp += n;
			}
			sp += stride;
		}
	}

	writer->stream.next_in = (Bytef*)writer->udata;
	writer->stream.avail_in = (uInt)(dp - writer->udata);
	do
	{
		writer->stream.next_out = writer->cdata;
		writer->stream.avail_out = (uInt)writer->csize;

		if (!finalband)
		{
			err = deflate(&writer->stream, Z_NO_FLUSH);
			if (err != Z_OK)
				fz_throw(ctx, FZ_ERROR_GENERIC, "compression error %d", err);
		}
		else
		{
			err = deflate(&writer->stream, Z_FINISH);
			if (err != Z_STREAM_END)
				fz_throw(ctx, FZ_ERROR_GENERIC, "compression error %d", err);
		}

		if (writer->stream.next_out != writer->cdata)
			putchunk(ctx, out, "IDAT", writer->cdata, writer->stream.next_out - writer->cdata);
	}
	while (writer->stream.avail_out == 0);
}