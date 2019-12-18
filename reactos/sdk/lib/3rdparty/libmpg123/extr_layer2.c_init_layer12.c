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
 int* grp_3tab ; 
 int* grp_5tab ; 
 int* grp_9tab ; 

void init_layer12(void)
{
	const int base[3][9] =
	{
		{ 1 , 0, 2 , } ,
		{ 17, 18, 0 , 19, 20 , } ,
		{ 21, 1, 22, 23, 0, 24, 25, 2, 26 }
	};
	int i,j,k,l,len;
	const int tablen[3] = { 3 , 5 , 9 };
	int *itable;
	int *tables[3] = { grp_3tab , grp_5tab , grp_9tab };

	for(i=0;i<3;i++)
	{
		itable = tables[i];
		len = tablen[i];
		for(j=0;j<len;j++)
		for(k=0;k<len;k++)
		for(l=0;l<len;l++)
		{
			*itable++ = base[i][l];
			*itable++ = base[i][k];
			*itable++ = base[i][j];
		}
	}
}