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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  USHORT ;
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  BIOS_MISC_INTERRUPT ; 
 int /*<<< orphan*/  Int32Call (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MouseContext ; 
 int /*<<< orphan*/  getAX () ; 
 int /*<<< orphan*/  setAH (int) ; 
 int /*<<< orphan*/  setAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setAX (int /*<<< orphan*/ ) ; 

VOID BiosPs2Service(UCHAR Function)
{
    /* Save AX and BX */
    USHORT AX = getAX();
    // USHORT BX = getBX();

    /*
     * Set the parameters:
     * AL contains the character to print (already set),
     * BL contains the character attribute,
     * BH contains the video page to use.
     */
    // setBL(DOS_CHAR_ATTRIBUTE);
    // setBH(Bda->VideoPage);
    setAL(Function);

    /* Call the BIOS INT 15h, AH=C2h "Pointing Device BIOS Interface (PS)" */
    setAH(0xC2);
    Int32Call(&MouseContext, BIOS_MISC_INTERRUPT);

    /* Restore AX and BX */
    // setBX(BX);
    setAX(AX);
}