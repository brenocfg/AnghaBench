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
typedef  int uint8 ;
typedef  int uint16 ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  int /*<<< orphan*/  RDPCLIENT ;
typedef  scalar_t__ HBITMAP ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int BUFSIZE_MASK ; 
 int /*<<< orphan*/  DEBUG (char*) ; 
 int ID_MASK ; 
 int LONG_FORMAT ; 
 int MODE_MASK ; 
 int MODE_SHIFT ; 
 int PERSIST ; 
 int SQUARE ; 
 int /*<<< orphan*/  bitmap_decompress (int*,int,int,int*,int,int) ; 
 int /*<<< orphan*/  cache_put_bitmap (int /*<<< orphan*/ *,int,int,scalar_t__) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  in_uint16_be (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  in_uint8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  in_uint8p (int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  pstcache_save_bitmap (int /*<<< orphan*/ *,int,int,int*,int,int,int,int*) ; 
 scalar_t__ ui_create_bitmap (int /*<<< orphan*/ *,int,int,int*) ; 
 int y ; 

__attribute__((used)) static void
process_bmpcache2(RDPCLIENT * This, STREAM s, uint16 flags, BOOL compressed)
{
	HBITMAP bitmap;
	uint8 cache_id, cache_idx_low, width, height, Bpp;
	uint16 cache_idx, bufsize;
	uint8 *data, *bmpdata, *bitmap_id;

	bitmap_id = NULL;	/* prevent compiler warning */
	cache_id = flags & ID_MASK;
	Bpp = ((flags & MODE_MASK) >> MODE_SHIFT) - 2;

	if (flags & PERSIST)
	{
		in_uint8p(s, bitmap_id, 8);
	}

	if (flags & SQUARE)
	{
		in_uint8(s, width);
		height = width;
	}
	else
	{
		in_uint8(s, width);
		in_uint8(s, height);
	}

	in_uint16_be(s, bufsize);
	bufsize &= BUFSIZE_MASK;
	in_uint8(s, cache_idx);

	if (cache_idx & LONG_FORMAT)
	{
		in_uint8(s, cache_idx_low);
		cache_idx = ((cache_idx ^ LONG_FORMAT) << 8) + cache_idx_low;
	}

	in_uint8p(s, data, bufsize);

	DEBUG(("BMPCACHE2(compr=%d,flags=%x,cx=%d,cy=%d,id=%d,idx=%d,Bpp=%d,bs=%d)\n",
	       compressed, flags, width, height, cache_id, cache_idx, Bpp, bufsize));

	if (compressed)
	{
		bmpdata = (uint8 *) malloc(width * height * Bpp);

		if(bmpdata == NULL)
			return;

		if (!bitmap_decompress(bmpdata, width, height, data, bufsize, Bpp))
		{
			DEBUG(("Failed to decompress bitmap data\n"));
			free(bmpdata);
			return;
		}
	}
	else
	{
#if 0
		for (y = 0; y < height; y++)
			memcpy(&bmpdata[(height - y - 1) * (width * Bpp)],
			       &data[y * (width * Bpp)], width * Bpp);
#else
		bmpdata = data;
#endif
	}

	bitmap = ui_create_bitmap(This, width, height, bmpdata);

	if (bitmap)
	{
		cache_put_bitmap(This, cache_id, cache_idx, bitmap);
		if (flags & PERSIST)
			pstcache_save_bitmap(This, cache_id, cache_idx, bitmap_id, width, height,
					     width * height * Bpp, bmpdata);
	}
	else
	{
		DEBUG(("process_bmpcache2: ui_create_bitmap failed\n"));
	}

	if (compressed)
		free(bmpdata);
}