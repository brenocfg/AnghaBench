#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  input ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_6__ {int /*<<< orphan*/  AsciiChar; } ;
struct TYPE_7__ {TYPE_1__ uChar; scalar_t__ bKeyDown; } ;
struct TYPE_8__ {TYPE_2__ KeyEvent; } ;
struct TYPE_9__ {scalar_t__ EventType; TYPE_3__ Event; } ;
typedef  int /*<<< orphan*/  PCSTR ;
typedef  TYPE_4__ INPUT_RECORD ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FlushConsoleInputBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ KEY_EVENT ; 
 int /*<<< orphan*/  PrintMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadConsoleInput (int /*<<< orphan*/ ,TYPE_4__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,int) ; 
 int tolower (int /*<<< orphan*/ ) ; 

int InputChar(ULONG msg, PCSTR ans)
{
	HANDLE			hStdIn;
	INPUT_RECORD	input;
	DWORD			result;
	int				reply;

	PrintMessage(msg);
	fflush(NULL);

	hStdIn	= GetStdHandle(STD_INPUT_HANDLE);

	FlushConsoleInputBuffer(hStdIn);

	for (;;) {
		ReadConsoleInput(hStdIn, &input, sizeof(input), &result);

		if (input.EventType == KEY_EVENT &&
			input.Event.KeyEvent.bKeyDown) {

			reply = tolower(input.Event.KeyEvent.uChar.AsciiChar);

			if (strchr(ans, reply)) {
				break;
			}
		}
	}

	printf("%c\n", reply);

	return reply;
}