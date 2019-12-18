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
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_2__ {void* boldital_font; void* ital_font; void* bold_font; void* norm_font; int /*<<< orphan*/  char_height; int /*<<< orphan*/  char_ascent; int /*<<< orphan*/  char_width; } ;

/* Variables and functions */
 int OK ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  gui_resize_shell (int,int) ; 
 int /*<<< orphan*/  vim_strcat (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vim_strncpy (int /*<<< orphan*/ *,char*,int) ; 
 void* vim_strsave (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vimjs_get_char_height () ; 
 int /*<<< orphan*/  vimjs_get_char_width () ; 
 int vimjs_get_window_height () ; 
 int vimjs_get_window_width () ; 
 int /*<<< orphan*/  vimjs_init_font (char*) ; 

int
gui_mch_init_font(char_u *font_name, int fontset)
{
    vimjs_init_font((char*)font_name);

    gui.char_width = vimjs_get_char_width();
    gui.char_height = vimjs_get_char_height();
    gui.char_ascent = gui.char_height;

    char_u buf[100];

    gui.norm_font = vim_strsave(font_name);
        
    vim_strncpy(buf, "bold ", 99); // should report 1 less to vim_strncpy 
    vim_strcat(buf, font_name, 100);
    gui.bold_font = vim_strsave(buf);

    vim_strncpy(buf, "italic ", 99); // should report 1 less to vim_strncpy 
    vim_strcat(buf, font_name, 100);
    gui.ital_font = vim_strsave(buf);

    vim_strncpy(buf, "bold italic ", 99); // should report 1 less to vim_strncpy 
    vim_strcat(buf, font_name, 100);
    gui.boldital_font = vim_strsave(buf);

    int w,h;
    w = vimjs_get_window_width();
    h = vimjs_get_window_height();
    gui_resize_shell(w, h);

    return OK;
}