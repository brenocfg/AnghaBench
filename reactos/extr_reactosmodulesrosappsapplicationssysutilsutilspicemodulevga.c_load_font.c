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
typedef  int UCHAR ;
typedef  int* PUCHAR ;

/* Variables and functions */
 int BYTESPERFONT ; 
 int FONTENTRIES ; 
 int /*<<< orphan*/  map_font_memory () ; 
 int* pFontBufferVga ; 
 int /*<<< orphan*/  unmap_font_memory () ; 

void load_font(UCHAR* graph_table,int bEnter)
{
	PUCHAR FontBase = pFontBufferVga;
	int i,j;
	map_font_memory();

	if(bEnter)
	{
#ifdef VGA_EXTENDED
		for (i=0; i < FONTENTRIES; i++)
			for (j=0; j < 8; j++)
					FontBase[i*32+j] = graph_table[i*BYTESPERFONT+j];
#else // VGA_EXTENDED
		for (i=0; i < FONTENTRIES; i++)
			for (j=0; j < 16; j++)
					FontBase[i*32+j] = graph_table[i*BYTESPERFONT+(j/2)] << (j&1);
#endif // VGA_EXTENDED
	}
	else
	{
		for (i=0; i < FONTENTRIES; i++)
			for (j=0; j < 16; j++)
					FontBase[i*32+j] = graph_table[i*16+j];
	}

	unmap_font_memory();
}