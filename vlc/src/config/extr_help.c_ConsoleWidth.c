#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct winsize {int ws_col; int uw_height; int uw_vs; } ;
struct uwdata {int ws_col; int uw_height; int uw_vs; } ;
struct TYPE_4__ {int X; } ;
struct TYPE_5__ {TYPE_1__ dwSize; } ;
typedef  TYPE_2__ CONSOLE_SCREEN_BUFFER_INFO ;

/* Variables and functions */
 scalar_t__ GetConsoleScreenBufferInfo (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int /*<<< orphan*/  WIOCGETD ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct winsize*) ; 

__attribute__((used)) static unsigned ConsoleWidth(void)
{
#ifdef TIOCGWINSZ
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0)
        return ws.ws_col;
#endif
#ifdef WIOCGETD
    struct uwdata uw;

    if (ioctl(STDOUT_FILENO, WIOCGETD, &uw) == 0)
        return uw.uw_height / uw.uw_vs;
#endif
#if defined (_WIN32) && !VLC_WINSTORE_APP
    CONSOLE_SCREEN_BUFFER_INFO buf;

    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buf))
        return buf.dwSize.X;
#endif
    return 80;
}