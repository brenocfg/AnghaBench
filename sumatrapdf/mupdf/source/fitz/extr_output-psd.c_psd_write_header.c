#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int w; int h; int s; int n; int alpha; int xres; int yres; int /*<<< orphan*/ * seps; int /*<<< orphan*/ * out; } ;
struct TYPE_13__ {int num_additive; TYPE_1__ super; } ;
typedef  TYPE_4__ psd_band_writer ;
typedef  int /*<<< orphan*/  fz_separations ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_11__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_12__ {TYPE_2__ icc; } ;
struct TYPE_14__ {int n; TYPE_3__ u; } ;
typedef  TYPE_5__ fz_colorspace ;
typedef  int /*<<< orphan*/  fz_band_writer ;

/* Variables and functions */
 size_t fz_buffer_storage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char**) ; 
 int /*<<< orphan*/  fz_colorspace_is_subtractive (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  fz_default_color_params ; 
 TYPE_5__* fz_device_cmyk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_separation_equivalent (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_5__*,float*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* fz_separation_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  fz_write_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_write_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  fz_write_int16_be (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_write_int32_be (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void
psd_write_header(fz_context *ctx, fz_band_writer *writer_, fz_colorspace *cs)
{
	psd_band_writer *writer = (psd_band_writer *)(void *)writer_;
	fz_output *out = writer->super.out;
	int w = writer->super.w;
	int h = writer->super.h;
	int s = writer->super.s;
	int n = writer->super.n;
	int c = n - writer->super.alpha - s;
	fz_separations *seps = writer->super.seps;
	int i;
	size_t len;
	static const char psdsig[12] = { '8', 'B', 'P', 'S', 0, 1, 0, 0, 0, 0, 0, 0 };
	static const char ressig[4] = { '8', 'B', 'I', 'M' };
	unsigned char *data;
	size_t size;
	fz_colorspace *cs_cmyk = cs;

#if FZ_ENABLE_ICC
	size = fz_buffer_storage(ctx, cs->u.icc.buffer, &data);
#else
	size = 0;
	data = NULL;
#endif

	if (cs->n != 4)
		cs_cmyk = fz_device_cmyk(ctx);

	if (!fz_colorspace_is_subtractive(ctx, cs))
		writer->num_additive = cs->n;

	/* File Header Section */
	fz_write_data(ctx, out, psdsig, 12);
	fz_write_int16_be(ctx, out, n);
	fz_write_int32_be(ctx, out, h);
	fz_write_int32_be(ctx, out, w);
	fz_write_int16_be(ctx, out, 8); /* bits per channel */

	switch (c)
	{
	case 0:
	case 1:
		fz_write_int16_be(ctx, out, 1); /* Greyscale */
		break;
	case 3:
		fz_write_int16_be(ctx, out, 3); /* RGB */
		break;
	case 4:
		fz_write_int16_be(ctx, out, 4); /* CMYK */
		break;
	default:
		fz_write_int16_be(ctx, out, 7); /* Multichannel */
		break;
	}

	/* Color Mode Data Section - empty */
	fz_write_int32_be(ctx, out, 0);

	/* Image Resources Section - Spot Names, Equivalent colors, resolution, ICC Profile */
	/* Spot names */
	len = 0;
	for (i = 0; i < s; i++)
	{
		const char *name = fz_separation_name(ctx, seps, i);
		char text[32];
		size_t len2;
		if (name == NULL)
		{
			fz_snprintf(text, sizeof text, "Spot%d", i-4);
			name = text;
		}
		len2 = strlen(name);
		if (len2 > 255)
			len2 = 255;
		len += len2 + 1;
	}

	/* Write the size of all the following resources */
	fz_write_int32_be(ctx, out,
			(s ? 12 + ((len + 1)&~1) : 0) +	/* Spot Names */
			(s ? 12 + (14 * s) : 0) +	/* DisplayInfo */
			28 +				/* Resolutions */
			(size ? (size+19)&~1 : 0));	/* ICC Profile */

	/* Spot names */
	if (s != 0)
	{
		fz_write_data(ctx, out, ressig, 4);
		fz_write_int16_be(ctx, out, 0x03EE);
		fz_write_int16_be(ctx, out, 0); /* PString */
		fz_write_int32_be(ctx, out, (len + 1)&~1);
		for (i = 0; i < s; i++) {
			size_t len2;
			const char *name = fz_separation_name(ctx, seps, i);
			char text[32];
			if (name == NULL)
			{
				fz_snprintf(text, sizeof text, "Spot%d", i-4);
				name = text;
			}
			len2 = strlen(name);
			if (len2 > 255)
				len2 = 255;
			fz_write_byte(ctx, out, len2);
			fz_write_data(ctx, out, name, len2);
		}
		if (len & 1)
		{
			fz_write_byte(ctx, out, 0);
		}

		/* DisplayInfo - Colors for each spot channel */
		fz_write_data(ctx, out, ressig, 4);
		fz_write_int16_be(ctx, out, 0x03EF);
		fz_write_int16_be(ctx, out, 0); /* PString */
		fz_write_int32_be(ctx, out, 14 * s); /* Length */
		for (i = 0; i < s; i++) {
			float cmyk[4];
			fz_separation_equivalent(ctx, seps, i, cs_cmyk, cmyk, NULL, fz_default_color_params);
			fz_write_int16_be(ctx, out, 02); /* CMYK */
			/* PhotoShop stores all component values as if they were additive. */
			fz_write_int16_be(ctx, out, 65535 * (1-cmyk[0]));/* Cyan */
			fz_write_int16_be(ctx, out, 65535 * (1-cmyk[1]));/* Magenta */
			fz_write_int16_be(ctx, out, 65535 * (1-cmyk[2]));/* Yellow */
			fz_write_int16_be(ctx, out, 65535 * (1-cmyk[3]));/* Black */
			fz_write_int16_be(ctx, out, 0); /* Opacity 0 to 100 */
			fz_write_byte(ctx, out, 2); /* Don't know */
			fz_write_byte(ctx, out, 0); /* Padding - Always Zero */
		}
	}

	/* ICC Profile - (size + 19)&~1 bytes */
	if (size != 0)
	{
		/* Image Resource block */
		fz_write_data(ctx, out, ressig, 4);
		fz_write_int16_be(ctx, out, 0x40f); /* ICC Profile */
		fz_write_data(ctx, out, "\x07Profile", 8); /* Profile name (must be even!) */
		fz_write_int32_be(ctx, out, size);
		fz_write_data(ctx, out, data, size); /* Actual data */
		if (size & 1)
			fz_write_byte(ctx, out, 0); /* Pad to even */
	}

	/* Image resolution - 28 bytes */
	fz_write_data(ctx, out, ressig, 4);
	fz_write_int16_be(ctx, out, 0x03ED);
	fz_write_int16_be(ctx, out, 0); /* PString */
	fz_write_int32_be(ctx, out, 16); /* Length */
	/* Resolution is specified as a fixed 16.16 bits */
	fz_write_int32_be(ctx, out, writer->super.xres);
	fz_write_int16_be(ctx, out, 1); /* width:  1 --> resolution is pixels per inch */
	fz_write_int16_be(ctx, out, 1); /* width:  1 --> resolution is pixels per inch */
	fz_write_int32_be(ctx, out, writer->super.yres);
	fz_write_int16_be(ctx, out, 1); /* height:  1 --> resolution is pixels per inch */
	fz_write_int16_be(ctx, out, 1); /* height:  1 --> resolution is pixels per inch */

	/* Layer and Mask Information Section */
	fz_write_int32_be(ctx, out, 0);

	/* Image Data Section */
	fz_write_int16_be(ctx, out, 0); /* Raw image data */
}