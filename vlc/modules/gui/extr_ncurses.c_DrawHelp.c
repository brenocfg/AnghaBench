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
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ intf_thread_t ;
struct TYPE_5__ {scalar_t__ color; } ;
typedef  TYPE_2__ intf_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  C_CATEGORY ; 
 int /*<<< orphan*/  C_DEFAULT ; 
 int /*<<< orphan*/  H (char*) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  color_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int DrawHelp(intf_thread_t *intf)
{
    intf_sys_t *sys = intf->p_sys;
    int l = 0;

#define H(a) MainBoxWrite(sys, l++, a)

    if (sys->color) color_set(C_CATEGORY, NULL);
    H(_("[Display]"));
    if (sys->color) color_set(C_DEFAULT, NULL);
    H(_(" h,H                    Show/Hide help box"));
    H(_(" i                      Show/Hide info box"));
    H(_(" M                      Show/Hide metadata box"));
    H(_(" L                      Show/Hide messages box"));
    H(_(" P                      Show/Hide playlist box"));
    H(_(" B                      Show/Hide filebrowser"));
    H(_(" S                      Show/Hide statistics box"));
    H(_(" Esc                    Close Add/Search entry"));
    H(_(" Ctrl-l                 Refresh the screen"));
    H("");

    if (sys->color) color_set(C_CATEGORY, NULL);
    H(_("[Global]"));
    if (sys->color) color_set(C_DEFAULT, NULL);
    H(_(" q, Q, Esc              Quit"));
    H(_(" s                      Stop"));
    H(_(" <space>                Pause/Play"));
    H(_(" f                      Toggle Fullscreen"));
    H(_(" c                      Cycle through audio tracks"));
    H(_(" v                      Cycle through subtitles tracks"));
    H(_(" b                      Cycle through video tracks"));
    H(_(" n, p                   Next/Previous playlist item"));
    H(_(" [, ]                   Next/Previous title"));
    H(_(" <, >                   Next/Previous chapter"));
    /* xgettext: You can use ← and → characters */
    H(_(" <left>,<right>         Seek -/+ 1%%"));
    H(_(" a, z                   Volume Up/Down"));
    H(_(" m                      Mute"));
    /* xgettext: You can use ↑ and ↓ characters */
    H(_(" <up>,<down>            Navigate through the box line by line"));
    /* xgettext: You can use ⇞ and ⇟ characters */
    H(_(" <pageup>,<pagedown>    Navigate through the box page by page"));
    /* xgettext: You can use ↖ and ↘ characters */
    H(_(" <start>,<end>          Navigate to start/end of box"));
    H("");

    if (sys->color) color_set(C_CATEGORY, NULL);
    H(_("[Playlist]"));
    if (sys->color) color_set(C_DEFAULT, NULL);
    H(_(" r                      Toggle Random playing"));
    H(_(" l                      Toggle Loop Playlist"));
    H(_(" R                      Toggle Repeat item"));
    H(_(" o                      Order Playlist by title"));
    H(_(" O                      Reverse order Playlist by title"));
    H(_(" g                      Go to the current playing item"));
    H(_(" /                      Look for an item"));
    H(_(" ;                      Look for the next item"));
    H(_(" A                      Add an entry"));
    /* xgettext: You can use ⌫ character to translate <backspace> */
    H(_(" D, <backspace>, <del>  Delete an entry"));
    H(_(" e                      Eject (if stopped)"));
    H("");

    if (sys->color) color_set(C_CATEGORY, NULL);
    H(_("[Filebrowser]"));
    if (sys->color) color_set(C_DEFAULT, NULL);
    H(_(" <enter>                Add the selected file to the playlist"));
    H(_(" <space>                Add the selected directory to the playlist"));
    H(_(" .                      Show/Hide hidden files"));
    H("");

    if (sys->color) color_set(C_CATEGORY, NULL);
    H(_("[Player]"));
    if (sys->color) color_set(C_DEFAULT, NULL);
    /* xgettext: You can use ↑ and ↓ characters */
    H(_(" <up>,<down>            Seek +/-5%%"));

#undef H
    return l;
}