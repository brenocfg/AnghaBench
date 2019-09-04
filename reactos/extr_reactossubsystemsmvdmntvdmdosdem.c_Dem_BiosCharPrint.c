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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  USHORT ;
struct TYPE_2__ {int /*<<< orphan*/  VideoPage; } ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  BIOS_VIDEO_INTERRUPT ; 
 TYPE_1__* Bda ; 
 int /*<<< orphan*/  DEFAULT_ATTRIBUTE ; 
 int /*<<< orphan*/  DosContext ; 
 int /*<<< orphan*/  Int32Call (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getAX () ; 
 int /*<<< orphan*/  getBX () ; 
 int /*<<< orphan*/  setAH (int) ; 
 int /*<<< orphan*/  setAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setAX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setBH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setBL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setBX (int /*<<< orphan*/ ) ; 

VOID Dem_BiosCharPrint(CHAR Character)
{
    /* Save AX and BX */
    USHORT AX = getAX();
    USHORT BX = getBX();

    /*
     * Set the parameters:
     * AL contains the character to print,
     * BL contains the character attribute,
     * BH contains the video page to use.
     */
    setAL(Character);
    setBL(DEFAULT_ATTRIBUTE);
    setBH(Bda->VideoPage);

    /* Call the BIOS INT 10h, AH=0Eh "Teletype Output" */
    setAH(0x0E);
    Int32Call(&DosContext, BIOS_VIDEO_INTERRUPT);

    /* Restore AX and BX */
    setBX(BX);
    setAX(AX);
}