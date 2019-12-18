#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int uint16 ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  int /*<<< orphan*/  RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*) ; 
 int /*<<< orphan*/  DEBUG_RDP5 (char*) ; 
 scalar_t__ bitmap_decompress (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_uint16_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  in_uint8a (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  in_uint8p (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  in_uint8s (int /*<<< orphan*/ ,int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  ui_paint_bitmap (int /*<<< orphan*/ *,int,int,int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 
 scalar_t__ xmalloc (int) ; 

void
process_bitmap_updates(RDPCLIENT * This, STREAM s)
{
	uint16 num_updates;
	uint16 left, top, right, bottom, width, height;
	uint16 cx, cy, bpp, Bpp, compress, bufsize, size;
	uint8 *data, *bmpdata;
	int i;

	in_uint16_le(s, num_updates);

	for (i = 0; i < num_updates; i++)
	{
		in_uint16_le(s, left);
		in_uint16_le(s, top);
		in_uint16_le(s, right);
		in_uint16_le(s, bottom);
		in_uint16_le(s, width);
		in_uint16_le(s, height);
		in_uint16_le(s, bpp);
		Bpp = (bpp + 7) / 8;
		in_uint16_le(s, compress);
		in_uint16_le(s, bufsize);

		cx = right - left + 1;
		cy = bottom - top + 1;

		DEBUG(("BITMAP_UPDATE(l=%d,t=%d,r=%d,b=%d,w=%d,h=%d,Bpp=%d,cmp=%d)\n",
		       left, top, right, bottom, width, height, Bpp, compress));

		if (!compress)
		{
#if 0
			int y;
			bmpdata = (uint8 *) xmalloc(width * height * Bpp);
			for (y = 0; y < height; y++)
			{
				in_uint8a(s, &bmpdata[(height - y - 1) * (width * Bpp)],
					  width * Bpp);
			}
			ui_paint_bitmap(This, left, top, cx, cy, width, height, bmpdata);
			xfree(bmpdata);
#else
			in_uint8p(s, bmpdata, width * height * Bpp);
			ui_paint_bitmap(This, left, top, cx, cy, width, height, bmpdata);
#endif
			continue;
		}


		if (compress & 0x400)
		{
			size = bufsize;
		}
		else
		{
			in_uint8s(s, 2);	/* pad */
			in_uint16_le(s, size);
			in_uint8s(s, 4);	/* line_size, final_size */
		}
		in_uint8p(s, data, size);
		bmpdata = (uint8 *) malloc(width * height * Bpp);

		if(bmpdata == NULL)
			return;

		if (bitmap_decompress(bmpdata, width, height, data, size, Bpp))
		{
			ui_paint_bitmap(This, left, top, cx, cy, width, height, bmpdata);
		}
		else
		{
			DEBUG_RDP5(("Failed to decompress data\n"));
		}

		free(bmpdata);
	}
}