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
typedef  int /*<<< orphan*/  vncBuffer ;
typedef  size_t uint8 ;
typedef  int /*<<< orphan*/  HGLYPH ;

/* Variables and functions */
 size_t* reverseByte ; 
 scalar_t__ rfbEndianTest ; 
 int /*<<< orphan*/ * vncNewBuffer (int,int,int) ; 
 int /*<<< orphan*/  vncSetPixel (int /*<<< orphan*/ *,int,int,int) ; 

HGLYPH
ui_create_glyph(int width, int height, uint8 * data)
{
	int x, y;
	vncBuffer *buf;

	buf = vncNewBuffer(width, height, 8);

	//data is padded to multiple of 16bit line lengths
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			int byte = x / 8 + (y * ((width + 7) / 8));
			byte = rfbEndianTest ? reverseByte[data[byte]] : data[byte];
			byte = (byte >> (x & 7)) & 0x01;
			vncSetPixel(buf, x, y, byte ? 0x7f : 0x00);
		}
	}

	return (HGLYPH) buf;
}