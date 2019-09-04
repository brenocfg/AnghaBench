#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t WORD ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_2__ {size_t VideoPage; size_t ScreenColumns; int /*<<< orphan*/ * CursorPosition; } ;
typedef  size_t BYTE ;

/* Variables and functions */
 TYPE_1__* Bda ; 
 int /*<<< orphan*/  HIBYTE (size_t) ; 
 int /*<<< orphan*/  IOWriteB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOBYTE (size_t) ; 
 int /*<<< orphan*/  MAKEWORD (size_t,size_t) ; 
 int /*<<< orphan*/  VGA_CRTC_CURSOR_LOC_HIGH_REG ; 
 int /*<<< orphan*/  VGA_CRTC_CURSOR_LOC_LOW_REG ; 
 int /*<<< orphan*/  VGA_CRTC_DATA ; 
 int /*<<< orphan*/  VGA_CRTC_INDEX ; 

__attribute__((used)) static VOID VidBiosSetCursorPosition(BYTE Row, BYTE Column, BYTE Page)
{
    /* Update the position in the BDA */
    Bda->CursorPosition[Page] = MAKEWORD(Column, Row);

    /* Check if this is the current video page */
    if (Page == Bda->VideoPage)
    {
        WORD Offset = Row * Bda->ScreenColumns + Column;

        /* Modify the CRTC registers */
        IOWriteB(VGA_CRTC_INDEX, VGA_CRTC_CURSOR_LOC_LOW_REG);
        IOWriteB(VGA_CRTC_DATA , LOBYTE(Offset));
        IOWriteB(VGA_CRTC_INDEX, VGA_CRTC_CURSOR_LOC_HIGH_REG);
        IOWriteB(VGA_CRTC_DATA , HIBYTE(Offset));
    }
}