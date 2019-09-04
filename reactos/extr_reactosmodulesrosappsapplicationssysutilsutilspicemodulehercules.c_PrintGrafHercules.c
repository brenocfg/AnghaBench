#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
typedef  scalar_t__ UCHAR ;
struct TYPE_4__ {scalar_t__ bkcol; scalar_t__ fgcol; } ;
struct TYPE_5__ {TYPE_1__ bits; } ;
struct TYPE_6__ {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/ * PUCHAR ;

/* Variables and functions */
 scalar_t__ COLOR_BACKGROUND ; 
 scalar_t__ COLOR_CAPTION ; 
 scalar_t__ COLOR_FOREGROUND ; 
 scalar_t__ COLOR_TEXT ; 
 TYPE_3__ attr ; 
 int /*<<< orphan*/ * cGraphTable ; 
 int /*<<< orphan*/  pScreenBufferHercules ; 
 int* pVgaOffset ; 

void PrintGrafHercules(ULONG x,ULONG y,UCHAR c)
{
    ULONG i;
    PUCHAR p;
    ULONG _line = y<<3;

	if(!pScreenBufferHercules)
		return;

    p=&cGraphTable[(ULONG)c<<3];

    if((attr.u.bits.bkcol == COLOR_FOREGROUND && attr.u.bits.fgcol == COLOR_BACKGROUND) ||
       (attr.u.bits.bkcol == COLOR_CAPTION && attr.u.bits.fgcol == COLOR_TEXT) )
	    for(i=0 ;i<8 ;i++,_line++)
	    {
            *(PUCHAR)(pVgaOffset[_line & 0x3] + ( 90* (_line >> 2) ) + x) = ~*p++;
        }
    else
	    for(i=0 ;i<8 ;i++,_line++)
	    {
            *(PUCHAR)(pVgaOffset[_line & 0x3] + ( 90* (_line >> 2) ) + x) = *p++;
        }
}