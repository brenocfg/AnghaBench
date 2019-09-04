#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  FlushKeyboardQueue; int /*<<< orphan*/  (* GetKeyPolled ) () ;} ;
struct TYPE_3__ {int /*<<< orphan*/  SetBackgroundColor; int /*<<< orphan*/  SetForegroundColor; int /*<<< orphan*/  HideCursor; int /*<<< orphan*/  ShowCursor; int /*<<< orphan*/  RestoreGraphicsState; int /*<<< orphan*/  SaveGraphicsState; int /*<<< orphan*/  PrintCursor; int /*<<< orphan*/  PrintLogo; int /*<<< orphan*/  HatchLine; int /*<<< orphan*/  InvertLine; int /*<<< orphan*/  ClrLine; int /*<<< orphan*/  Flush; int /*<<< orphan*/  PrintGraf; int /*<<< orphan*/  CopyLineTo; } ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ClrLineSerial ; 
 scalar_t__ Connect (int,int) ; 
 int /*<<< orphan*/  CopyLineToSerial ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  EmptyRingBuffer () ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FRAMEBUFFER_SIZE ; 
 int /*<<< orphan*/  FlushKeyboardQueueSerial ; 
 int /*<<< orphan*/  FlushSerial ; 
 int GLOBAL_SCREEN_HEIGHT ; 
 int GLOBAL_SCREEN_WIDTH ; 
 int /*<<< orphan*/  GetKeyPolledSerial () ; 
 int /*<<< orphan*/  HatchLineSerial ; 
 int /*<<< orphan*/  HideCursorSerial ; 
 int /*<<< orphan*/  InvertLineSerial ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int /*<<< orphan*/  NONPAGEDPOOL ; 
 scalar_t__ PICE_malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrintCursorSerial ; 
 int /*<<< orphan*/  PrintGrafSerial ; 
 int /*<<< orphan*/  PrintLogoSerial ; 
 int /*<<< orphan*/  RestoreGraphicsStateSerial ; 
 int /*<<< orphan*/  SaveGraphicsStateSerial ; 
 int /*<<< orphan*/  SetBackgroundColorSerial ; 
 int /*<<< orphan*/  SetForegroundColorSerial ; 
 int /*<<< orphan*/  SetWindowGeometry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetupSerial (int,int) ; 
 int /*<<< orphan*/  ShowCursorSerial ; 
 scalar_t__ TRUE ; 
 TYPE_2__ ihandlers ; 
 TYPE_1__ ohandlers ; 
 scalar_t__ pScreenBufferSerial ; 
 int /*<<< orphan*/  wWindowSerial ; 

BOOLEAN ConsoleInitSerial(void)
{
	BOOLEAN bResult = FALSE;

    ENTER_FUNC();

    ohandlers.CopyLineTo            = CopyLineToSerial;
    ohandlers.PrintGraf             = PrintGrafSerial;
    ohandlers.Flush                 = FlushSerial;
    ohandlers.ClrLine               = ClrLineSerial;
    ohandlers.InvertLine            = InvertLineSerial;
    ohandlers.HatchLine             = HatchLineSerial;
    ohandlers.PrintLogo             = PrintLogoSerial;
    ohandlers.PrintCursor           = PrintCursorSerial;
    ohandlers.SaveGraphicsState     = SaveGraphicsStateSerial;
    ohandlers.RestoreGraphicsState  = RestoreGraphicsStateSerial;
    ohandlers.ShowCursor            = ShowCursorSerial;
    ohandlers.HideCursor            = HideCursorSerial;
    ohandlers.SetForegroundColor    = SetForegroundColorSerial;
    ohandlers.SetBackgroundColor    = SetBackgroundColorSerial;

    ihandlers.GetKeyPolled          = GetKeyPolledSerial;
    ihandlers.FlushKeyboardQueue    = FlushKeyboardQueueSerial;

    SetWindowGeometry(wWindowSerial);

    GLOBAL_SCREEN_WIDTH = 80;
    GLOBAL_SCREEN_HEIGHT = 60;

	pScreenBufferSerial = PICE_malloc(FRAMEBUFFER_SIZE, NONPAGEDPOOL);

    if(pScreenBufferSerial)
    {
	    bResult = TRUE;

        EmptyRingBuffer();

        SetupSerial(1,115200);

        // connect to terminal, if none's there, we give up
        bResult = Connect(GLOBAL_SCREEN_WIDTH,GLOBAL_SCREEN_HEIGHT);

        if(bResult)
        {
            GetKeyPolledSerial();
        }
    }

    LEAVE_FUNC();

	return bResult;
}