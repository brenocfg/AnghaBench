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
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/ * PUCHAR ;

/* Variables and functions */
 int FONTENTRIES ; 
 int /*<<< orphan*/  map_font_memory () ; 
 int /*<<< orphan*/ * pFontBufferVga ; 
 int /*<<< orphan*/  unmap_font_memory () ; 

void save_font(UCHAR* graph_table)
{
	PUCHAR FontBase = pFontBufferVga;
	int i,j;
	map_font_memory();

	for (i=0; i < FONTENTRIES; i++)
		for (j=0; j < 16; j++)
				graph_table[i*16+j] = FontBase[i*32+j];

	unmap_font_memory();
}