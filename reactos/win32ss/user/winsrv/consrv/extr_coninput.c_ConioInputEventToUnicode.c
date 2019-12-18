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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {int /*<<< orphan*/  UnicodeChar; scalar_t__ AsciiChar; } ;
struct TYPE_7__ {TYPE_1__ uChar; } ;
struct TYPE_8__ {TYPE_2__ KeyEvent; } ;
struct TYPE_9__ {scalar_t__ EventType; TYPE_3__ Event; } ;
typedef  TYPE_4__* PINPUT_RECORD ;
typedef  int /*<<< orphan*/  PCONSOLE ;
typedef  scalar_t__ CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ConsoleInputAnsiToUnicodeChar (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ KEY_EVENT ; 

__attribute__((used)) static VOID
ConioInputEventToUnicode(PCONSOLE Console, PINPUT_RECORD InputEvent)
{
    if (InputEvent->EventType == KEY_EVENT)
    {
        CHAR AsciiChar = InputEvent->Event.KeyEvent.uChar.AsciiChar;
        InputEvent->Event.KeyEvent.uChar.AsciiChar = 0;
        ConsoleInputAnsiToUnicodeChar(Console,
                                      &InputEvent->Event.KeyEvent.uChar.UnicodeChar,
                                      &AsciiChar);
    }
}