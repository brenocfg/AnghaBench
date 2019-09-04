#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ cy; } ;
struct TYPE_6__ {int Count; int /*<<< orphan*/ * Value; } ;
typedef  TYPE_1__ ARGS ;

/* Variables and functions */
 int /*<<< orphan*/  DisplayMemory (TYPE_1__*) ; 
 int /*<<< orphan*/  DisplayRegs () ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 size_t OUTPUT_WINDOW ; 
 int /*<<< orphan*/  OldOffset ; 
 int /*<<< orphan*/  OldSelector ; 
 int /*<<< orphan*/  PICE_memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Print (size_t,char*) ; 
 int /*<<< orphan*/  PrintRingBuffer (scalar_t__) ; 
 int /*<<< orphan*/  PrintTemplate () ; 
 int /*<<< orphan*/  ShowStatusLine () ; 
 int /*<<< orphan*/  ShowStoppedMsg () ; 
 int /*<<< orphan*/  Unassemble (TYPE_1__*) ; 
 scalar_t__ ulLastDisassEndAddress ; 
 scalar_t__ ulLastDisassStartAddress ; 
 TYPE_2__* wWindow ; 

void RepaintDesktop(void)
{
    ARGS Args;

    ENTER_FUNC();

    PrintTemplate();

    DisplayRegs();

    // display data window
	Args.Value[0]=OldSelector;
	Args.Value[1]=OldOffset;
	Args.Count=2;
	DisplayMemory(&Args);

    // disassembly from current address
    PICE_memset(&Args,0,sizeof(ARGS));
    // make unassembler refresh all again
    ulLastDisassStartAddress=ulLastDisassEndAddress=0;
	Args.Count=0;
	Unassemble(&Args);

    PrintRingBuffer(wWindow[OUTPUT_WINDOW].cy-1);
    Print(OUTPUT_WINDOW,"");

    ShowStoppedMsg();
    ShowStatusLine();

    LEAVE_FUNC();
}