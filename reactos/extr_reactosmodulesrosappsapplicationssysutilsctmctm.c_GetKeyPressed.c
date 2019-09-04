#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int wVirtualKeyCode; scalar_t__ bKeyDown; } ;
struct TYPE_6__ {TYPE_1__ KeyEvent; } ;
struct TYPE_7__ {scalar_t__ EventType; TYPE_2__ Event; } ;
typedef  TYPE_3__ INPUT_RECORD ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ KEY_EVENT ; 
 int /*<<< orphan*/  ReadConsoleInput (int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hStdin ; 

unsigned int GetKeyPressed(int events)
{
	DWORD bytesRead;
	INPUT_RECORD record;
	int i;


	for (i=0; i<events; i++)
	{
		if (!ReadConsoleInput(hStdin, &record, 1, &bytesRead)) {
			return 0;
		}

		if (record.EventType == KEY_EVENT && record.Event.KeyEvent.bKeyDown)
			return record.Event.KeyEvent.wVirtualKeyCode;//.uChar.AsciiChar;
	}

	return 0;
}