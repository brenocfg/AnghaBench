#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int USHORT ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_5__ {scalar_t__ bkcol; scalar_t__ fgcol; } ;
struct TYPE_6__ {TYPE_1__ bits; } ;
struct TYPE_8__ {TYPE_2__ u; } ;
struct TYPE_7__ {int y; } ;
typedef  scalar_t__ PUCHAR ;
typedef  int BOOLEAN ;

/* Variables and functions */
 scalar_t__ COLOR_CAPTION ; 
 scalar_t__ COLOR_TEXT ; 
 size_t DATA_WINDOW ; 
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int GLOBAL_SCREEN_HEIGHT ; 
 int /*<<< orphan*/  GLOBAL_SCREEN_WIDTH ; 
 size_t OUTPUT_WINDOW ; 
 int /*<<< orphan*/  PICE_memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t SOURCE_WINDOW ; 
 TYPE_4__ attr ; 
 scalar_t__* pVgaOffset ; 
 TYPE_3__* wWindow ; 

void ClrLineHercules(ULONG line)
{
    ULONG j;
    BOOLEAN bTemplateLine=( (USHORT)line==wWindow[DATA_WINDOW].y-1 ||
                            (USHORT)line==wWindow[SOURCE_WINDOW].y-1 ||
                            (USHORT)line==wWindow[OUTPUT_WINDOW].y-1 ||
                            0);
	ULONG _line = line<<3;
    ULONG cc=0;
   	PUCHAR p;

//    ENTER_FUNC();

    if(line > GLOBAL_SCREEN_HEIGHT )
    {
        DPRINT((0,"ClrLineHercules(): line %u is out of screen\n",line));
        //LEAVE_FUNC();
        return;
    }

    if(attr.u.bits.bkcol == COLOR_CAPTION && attr.u.bits.fgcol == COLOR_TEXT )
        cc=~cc;

    if(bTemplateLine)
    {
	    for(j=0;j<8;j++,_line++)
	    {
            p = (PUCHAR)(pVgaOffset[_line&3] + (90*(_line>>2)) );

/*
			if(j==2 || j==5)cc=0xFF;
			else if(j==3)cc=0xaa;
			else if(j==4)cc=0x55;
			else cc = 0;*/
			if(j==2 || j==5)cc=0xFF;
			else cc = 0;

		    PICE_memset(p,(UCHAR)cc,GLOBAL_SCREEN_WIDTH);
	    }
    }
    else
    {
        for(j=0;j<8;j++,_line++)
        {
            p = (PUCHAR)(pVgaOffset[_line&3] + (90*(_line>>2)) );

            PICE_memset(p,(UCHAR)cc,GLOBAL_SCREEN_WIDTH);
        }
    }
    //LEAVE_FUNC();
}