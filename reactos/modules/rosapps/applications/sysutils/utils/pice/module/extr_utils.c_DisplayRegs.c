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
 int /*<<< orphan*/  COLOR_HILITE ; 
 scalar_t__ CurrentCS ; 
 scalar_t__ CurrentDS ; 
 scalar_t__ CurrentEAX ; 
 scalar_t__ CurrentEBP ; 
 scalar_t__ CurrentEBX ; 
 scalar_t__ CurrentECX ; 
 scalar_t__ CurrentEDI ; 
 scalar_t__ CurrentEDX ; 
 scalar_t__ CurrentEFL ; 
 scalar_t__ CurrentEIP ; 
 scalar_t__ CurrentES ; 
 scalar_t__ CurrentESI ; 
 scalar_t__ CurrentESP ; 
 scalar_t__ CurrentFS ; 
 scalar_t__ CurrentGS ; 
 scalar_t__ CurrentSS ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  Home (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 scalar_t__ OldCS ; 
 scalar_t__ OldDS ; 
 scalar_t__ OldEAX ; 
 scalar_t__ OldEBP ; 
 scalar_t__ OldEBX ; 
 scalar_t__ OldECX ; 
 scalar_t__ OldEDI ; 
 scalar_t__ OldEDX ; 
 scalar_t__ OldEFL ; 
 scalar_t__ OldEIP ; 
 scalar_t__ OldES ; 
 scalar_t__ OldESI ; 
 scalar_t__ OldESP ; 
 scalar_t__ OldFS ; 
 scalar_t__ OldGS ; 
 scalar_t__ OldSS ; 
 int /*<<< orphan*/  PICE_sprintf (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  Print (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  REGISTER_WINDOW ; 
 int /*<<< orphan*/  ResetColor () ; 
 int /*<<< orphan*/  SetForegroundColor (int /*<<< orphan*/ ) ; 
 scalar_t__ VisualizeFlags (scalar_t__) ; 
 int /*<<< orphan*/  WHITE ; 

void DisplayRegs(void)
{
    char tempDisplayRegs[48];

    ENTER_FUNC();

//	Clear(REGISTER_WINDOW);
	Home(REGISTER_WINDOW);
	// EAX
    Print(REGISTER_WINDOW,"EAX=");
	PICE_sprintf(tempDisplayRegs,"%.8X",CurrentEAX);
	if(OldEAX!=CurrentEAX)
	{
		SetForegroundColor(WHITE);
	}
	Print(REGISTER_WINDOW,tempDisplayRegs);
	if(OldEAX!=CurrentEAX)
	{
        ResetColor();
	}

	// EBX
    Print(REGISTER_WINDOW," EBX=");
	PICE_sprintf(tempDisplayRegs,"%.8X",CurrentEBX);
	if(OldEBX!=CurrentEBX)
	{
		SetForegroundColor(WHITE);
	}
	Print(REGISTER_WINDOW,tempDisplayRegs);
	if(OldEBX!=CurrentEBX)
	{
        ResetColor();
	}

	// ECX
    Print(REGISTER_WINDOW," ECX=");
	PICE_sprintf(tempDisplayRegs,"%.8X",CurrentECX);
	if(OldECX!=CurrentECX)
	{
		SetForegroundColor(WHITE);
	}
	Print(REGISTER_WINDOW,tempDisplayRegs);
	if(OldECX!=CurrentECX)
	{
        ResetColor();
	}

	// EDX
    Print(REGISTER_WINDOW," EDX=");
	PICE_sprintf(tempDisplayRegs,"%.8X",CurrentEDX);
	if(OldEDX!=CurrentEDX)
	{
		SetForegroundColor(COLOR_HILITE);
	}
	Print(REGISTER_WINDOW,tempDisplayRegs);
	if(OldEDX!=CurrentEDX)
	{
		ResetColor();
	}

	// ESI
    Print(REGISTER_WINDOW," ESI=");
	PICE_sprintf(tempDisplayRegs,"%.8X",CurrentESI);
	if(OldESI!=CurrentESI)
	{
		SetForegroundColor(COLOR_HILITE);
	}
	Print(REGISTER_WINDOW,tempDisplayRegs);
	if(OldESI!=CurrentESI)
	{
		ResetColor();
	}

	// EDI
    Print(REGISTER_WINDOW," EDI=");
	PICE_sprintf(tempDisplayRegs,"%.8X\n",CurrentEDI);
	if(OldEDI!=CurrentEDI)
	{
		SetForegroundColor(COLOR_HILITE);
	}
	Print(REGISTER_WINDOW,tempDisplayRegs);
	if(OldEDI!=CurrentEDI)
	{
		ResetColor();
	}

	// EBP
    Print(REGISTER_WINDOW,"EBP=");
	PICE_sprintf(tempDisplayRegs,"%.8X",CurrentEBP);
	if(OldEBP!=CurrentEBP)
	{
		SetForegroundColor(COLOR_HILITE);
	}
	Print(REGISTER_WINDOW,tempDisplayRegs);
	if(OldEBP!=CurrentEBP)
	{
		ResetColor();
	}

	// ESP
    Print(REGISTER_WINDOW," ESP=");
	PICE_sprintf(tempDisplayRegs,"%.8X",CurrentESP);
	if(OldESP!=CurrentESP)
	{
		SetForegroundColor(COLOR_HILITE);
	}
	Print(REGISTER_WINDOW,tempDisplayRegs);
	if(OldESP!=CurrentESP)
	{
		ResetColor();
	}

	// EIP
    Print(REGISTER_WINDOW," EIP=");
	PICE_sprintf(tempDisplayRegs,"%.8X",CurrentEIP);
	if(OldEIP!=CurrentEIP)
	{
		SetForegroundColor(COLOR_HILITE);
	}
	Print(REGISTER_WINDOW,tempDisplayRegs);
	if(OldEIP!=CurrentEIP)
	{
		ResetColor();
	}

	// EFL
    Print(REGISTER_WINDOW," EFLAGS=");
	PICE_sprintf(tempDisplayRegs,"%.8X",CurrentEFL);
	if(OldEFL!=CurrentEFL)
	{
		SetForegroundColor(COLOR_HILITE);
	}
	Print(REGISTER_WINDOW,tempDisplayRegs);
	if(OldEFL!=CurrentEFL)
	{
		ResetColor();
	}

	// visual flags
	PICE_sprintf(tempDisplayRegs," %s\n",VisualizeFlags(CurrentEFL));
	Print(REGISTER_WINDOW,tempDisplayRegs);

	// CS
    Print(REGISTER_WINDOW,"CS=");
	PICE_sprintf(tempDisplayRegs,"%.4X",CurrentCS);
	if(OldCS!=CurrentCS)
	{
		SetForegroundColor(COLOR_HILITE);
	}
	Print(REGISTER_WINDOW,tempDisplayRegs);
	if(OldCS!=CurrentCS)
	{
		ResetColor();
	}

	// DS
    Print(REGISTER_WINDOW,"  DS=");
	PICE_sprintf(tempDisplayRegs,"%.4X",CurrentDS);
	if(OldDS!=CurrentDS)
	{
		SetForegroundColor(COLOR_HILITE);
	}
	Print(REGISTER_WINDOW,tempDisplayRegs);
	if(OldDS!=CurrentDS)
	{
		ResetColor();
	}

	// ES
    Print(REGISTER_WINDOW,"  ES=");
	PICE_sprintf(tempDisplayRegs,"%.4X",CurrentES);
	if(OldES!=CurrentES)
	{
		SetForegroundColor(COLOR_HILITE);
	}
	Print(REGISTER_WINDOW,tempDisplayRegs);
	if(OldES!=CurrentES)
	{
		ResetColor();
	}

	// FS
    Print(REGISTER_WINDOW,"  FS=");
	PICE_sprintf(tempDisplayRegs,"%.4X",CurrentFS);
	if(OldFS!=CurrentFS)
	{
		SetForegroundColor(COLOR_HILITE);
	}
	Print(REGISTER_WINDOW,tempDisplayRegs);
	if(OldFS!=CurrentFS)
	{
		ResetColor();
	}

	// GS
    Print(REGISTER_WINDOW,"  GS=");
	PICE_sprintf(tempDisplayRegs,"%.4X",CurrentGS);
	if(OldGS!=CurrentGS)
	{
		ResetColor();
	}
	Print(REGISTER_WINDOW,tempDisplayRegs);
	if(OldGS!=CurrentGS)
	{
		ResetColor();
	}

	// SS
    Print(REGISTER_WINDOW,"  SS=");
	PICE_sprintf(tempDisplayRegs,"%.4X",CurrentSS);
	if(OldSS!=CurrentSS)
	{
		SetForegroundColor(COLOR_HILITE);
	}
	Print(REGISTER_WINDOW,tempDisplayRegs);
	if(OldSS!=CurrentSS)
	{
		ResetColor();
	}

    LEAVE_FUNC();
}