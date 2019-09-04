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
typedef  int ULONG ;
typedef  int /*<<< orphan*/ * PUSHORT ;

/* Variables and functions */
 int GLOBAL_SCREEN_WIDTH ; 
 scalar_t__* pVgaOffset ; 

void InvertLineHercules(ULONG line)
{
    ULONG i,j;
    ULONG _line = line<<3;
	PUSHORT p;

    //ENTER_FUNC();

	for(j=0;j<8;j++)
	{
		p=(PUSHORT)( pVgaOffset[_line&3] + (90*(_line>>2)) );
		for(i=0;i<(GLOBAL_SCREEN_WIDTH>>1);i++)
		{
			p[i]=~p[i];
		}
		_line++;
	}

    //LEAVE_FUNC();
}