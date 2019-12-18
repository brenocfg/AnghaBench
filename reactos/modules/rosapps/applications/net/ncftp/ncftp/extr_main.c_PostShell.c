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
 int /*<<< orphan*/  CloseHost () ; 
 int /*<<< orphan*/  CloseTrace () ; 
 int /*<<< orphan*/  DisposeReadline () ; 
 int /*<<< orphan*/  DisposeWinsock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EndLog () ; 
 int /*<<< orphan*/  Plug () ; 
 int /*<<< orphan*/  SavePrefs () ; 
 int /*<<< orphan*/  SetXtermTitle (char*) ; 

__attribute__((used)) static void
PostShell(void)
{
	SetXtermTitle("RESTORE");
	CloseHost();
	DisposeReadline();
	CloseTrace();
	SavePrefs();
	EndLog();
	Plug();
	DisposeWinsock(0);
}