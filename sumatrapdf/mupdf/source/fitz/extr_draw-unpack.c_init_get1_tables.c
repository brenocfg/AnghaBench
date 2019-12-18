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

/* Variables and functions */
 int get1 (unsigned char*,int) ; 
 int** get1_tab_1 ; 
 int** get1_tab_1p ; 
 int** get1_tab_255 ; 
 int** get1_tab_255p ; 

__attribute__((used)) static void
init_get1_tables(void)
{
	static int once = 0;
	unsigned char bits[1];
	int i, k, x;

	/* TODO: mutex lock here */

	if (once)
		return;

	for (i = 0; i < 256; i++)
	{
		bits[0] = i;
		for (k = 0; k < 8; k++)
		{
			x = get1(bits, k);

			get1_tab_1[i][k] = x;
			get1_tab_1p[i][k * 2] = x;
			get1_tab_1p[i][k * 2 + 1] = 255;

			get1_tab_255[i][k] = x * 255;
			get1_tab_255p[i][k * 2] = x * 255;
			get1_tab_255p[i][k * 2 + 1] = 255;
		}
	}

	once = 1;
}