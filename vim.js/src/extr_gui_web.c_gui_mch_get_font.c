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
typedef  int /*<<< orphan*/  char_u ;
typedef  char* GuiFont ;

/* Variables and functions */
 int /*<<< orphan*/  EMSG2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* NOFONT ; 
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_font ; 
 scalar_t__ vim_strsave (int /*<<< orphan*/ *) ; 
 scalar_t__ vimjs_check_font (char*) ; 

GuiFont
gui_mch_get_font(char_u *name, int giveErrorIfMissing)
{
    if(vimjs_check_font((char*)name)) 
        return (char*)vim_strsave(name);

    if (giveErrorIfMissing)
        EMSG2(_(e_font), name);
    return NOFONT;
}