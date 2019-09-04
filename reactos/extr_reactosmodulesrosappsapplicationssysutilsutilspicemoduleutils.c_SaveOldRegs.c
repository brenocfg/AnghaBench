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
 int /*<<< orphan*/  CurrentCS ; 
 int /*<<< orphan*/  CurrentDS ; 
 int /*<<< orphan*/  CurrentEAX ; 
 int /*<<< orphan*/  CurrentEBP ; 
 int /*<<< orphan*/  CurrentEBX ; 
 int /*<<< orphan*/  CurrentECX ; 
 int /*<<< orphan*/  CurrentEDI ; 
 int /*<<< orphan*/  CurrentEDX ; 
 int /*<<< orphan*/  CurrentEFL ; 
 int /*<<< orphan*/  CurrentEIP ; 
 int /*<<< orphan*/  CurrentES ; 
 int /*<<< orphan*/  CurrentESI ; 
 int /*<<< orphan*/  CurrentESP ; 
 int /*<<< orphan*/  CurrentFS ; 
 int /*<<< orphan*/  CurrentGS ; 
 int /*<<< orphan*/  CurrentSS ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int /*<<< orphan*/  OldCS ; 
 int /*<<< orphan*/  OldDS ; 
 int /*<<< orphan*/  OldEAX ; 
 int /*<<< orphan*/  OldEBP ; 
 int /*<<< orphan*/  OldEBX ; 
 int /*<<< orphan*/  OldECX ; 
 int /*<<< orphan*/  OldEDI ; 
 int /*<<< orphan*/  OldEDX ; 
 int /*<<< orphan*/  OldEFL ; 
 int /*<<< orphan*/  OldEIP ; 
 int /*<<< orphan*/  OldES ; 
 int /*<<< orphan*/  OldESI ; 
 int /*<<< orphan*/  OldESP ; 
 int /*<<< orphan*/  OldFS ; 
 int /*<<< orphan*/  OldGS ; 
 int /*<<< orphan*/  OldSS ; 

void SaveOldRegs(void)
{

    ENTER_FUNC();

    OldEAX=CurrentEAX;
	OldEBX=CurrentEBX;
	OldECX=CurrentECX;
	OldEDX=CurrentEDX;
	OldESI=CurrentESI;
	OldEDI=CurrentEDI;
	OldEBP=CurrentEBP;
	OldESP=CurrentESP;
	OldEIP=CurrentEIP;
	OldEFL=CurrentEFL;
	OldCS=CurrentCS;
	OldDS=CurrentDS;
	OldES=CurrentES;
	OldFS=CurrentFS;
	OldGS=CurrentGS;
	OldSS=CurrentSS;

    LEAVE_FUNC();
}