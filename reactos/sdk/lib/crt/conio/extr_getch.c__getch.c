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
struct TYPE_2__ {int /*<<< orphan*/  _file; } ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int ENABLE_ECHO_INPUT ; 
 int ENABLE_LINE_INPUT ; 
 scalar_t__ GetConsoleMode (scalar_t__,int*) ; 
 int /*<<< orphan*/  ReadConsoleA (scalar_t__,char*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetConsoleMode (scalar_t__,int) ; 
 scalar_t__ _get_osfhandle (int /*<<< orphan*/ ) ; 
 scalar_t__ char_avail ; 
 TYPE_1__* stdin ; 
 char ungot_char ; 

int _getch(void)
{
    DWORD NumberOfCharsRead = 0;
    char c;
    HANDLE ConsoleHandle;
    BOOL RestoreMode;
    DWORD ConsoleMode;

    if (char_avail) {
        c = ungot_char;
        char_avail = 0;
    } else {
        /*
         * _getch() is documented to NOT echo characters. Testing shows it
         * doesn't wait for a CR either. So we need to switch off
         * ENABLE_ECHO_INPUT and ENABLE_LINE_INPUT if they're currently
         * switched on.
         */
        ConsoleHandle = (HANDLE) _get_osfhandle(stdin->_file);
        RestoreMode = GetConsoleMode(ConsoleHandle, &ConsoleMode) &&
                      (0 != (ConsoleMode &
                             (ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT)));
        if (RestoreMode) {
            SetConsoleMode(ConsoleHandle,
                           ConsoleMode & (~ (ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT)));
        }
        ReadConsoleA((HANDLE)_get_osfhandle(stdin->_file),
		             &c,
		             1,
		             &NumberOfCharsRead,
		             NULL);
        if (RestoreMode) {
            SetConsoleMode(ConsoleHandle, ConsoleMode);
        }
    }
    if (c == 10)
        c = 13;
    return c;
}