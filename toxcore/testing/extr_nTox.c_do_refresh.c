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
 int HISTORY ; 
 int STRING_LENGTH_WRAPPED ; 
 int /*<<< orphan*/  clrtoeol () ; 
 int count_lines (char*) ; 
 scalar_t__* flag ; 
 char* input_line ; 
 int /*<<< orphan*/ * lines ; 
 int /*<<< orphan*/  move (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printw (char*,...) ; 
 int /*<<< orphan*/  refresh () ; 
 int /*<<< orphan*/  wrap (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrap_bars (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x ; 
 int y ; 

void do_refresh()
{
    int count = 0;
    char wrap_output[STRING_LENGTH_WRAPPED];
    int i;

    for (i = 0; i < HISTORY; i++) {
        if (flag[i])
            wrap_bars(wrap_output, lines[i], x);
        else
            wrap(wrap_output, lines[i], x);

        int L = count_lines(wrap_output);
        count = count + L;

        if (count < y) {
            move(y - 1 - count, 0);
            printw("%s", wrap_output);
            clrtoeol();
        }
    }

    move(y - 1, 0);
    clrtoeol();
    printw(">> ");
    printw("%s", input_line);
    clrtoeol();
    refresh();
}