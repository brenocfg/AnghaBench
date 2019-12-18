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
typedef  int /*<<< orphan*/  HBITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  DoBlt (int /*<<< orphan*/ ) ; 
 int W_HEIGHT ; 
 int W_WIDTH ; 
 unsigned int* dibits ; 

void UpdatePalette(HBITMAP hBM){
	int i,y;
	static unsigned int c=0;

	for(i=0;i<W_WIDTH;i++){
		for(y=0;y<=W_HEIGHT-1;y++)
			dibits[y*320+i] = c % 256;

		if (c > 512)
			c = 0;
		else
			c++; // It's operation of incrementing of c variable, not reference of a cool OO language :-)
	}

	DoBlt(hBM);
}