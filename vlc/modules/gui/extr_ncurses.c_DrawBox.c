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
 int /*<<< orphan*/  ACS_HLINE ; 
 int /*<<< orphan*/  ACS_LLCORNER ; 
 int /*<<< orphan*/  ACS_LRCORNER ; 
 int /*<<< orphan*/  ACS_ULCORNER ; 
 int /*<<< orphan*/  ACS_URCORNER ; 
 int /*<<< orphan*/  ACS_VLINE ; 
 int COLS ; 
 int /*<<< orphan*/  C_BOX ; 
 int /*<<< orphan*/  C_DEFAULT ; 
 int /*<<< orphan*/  color_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvaddch (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvhline (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvprintw (int,int,char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void DrawBox(int y, int h, bool color, const char *title)
{
    int w = COLS;
    if (w <= 3 || h <= 0)
        return;

    if (color) color_set(C_BOX, NULL);

    if (!title) title = "";
    int len = strlen(title);

    if (len > w - 2)
        len = w - 2;

    mvaddch(y, 0,    ACS_ULCORNER);
    mvhline(y, 1,  ACS_HLINE, (w-len-2)/2);
    mvprintw(y, 1+(w-len-2)/2, "%s", title);
    mvhline(y, (w-len)/2+len,  ACS_HLINE, w - 1 - ((w-len)/2+len));
    mvaddch(y, w-1,ACS_URCORNER);

    for (int i = 0; i < h; i++) {
        mvaddch(++y, 0,   ACS_VLINE);
        mvaddch(y, w-1, ACS_VLINE);
    }

    mvaddch(++y, 0,   ACS_LLCORNER);
    mvhline(y,   1,   ACS_HLINE, w - 2);
    mvaddch(y,   w-1, ACS_LRCORNER);
    if (color) color_set(C_DEFAULT, NULL);
}