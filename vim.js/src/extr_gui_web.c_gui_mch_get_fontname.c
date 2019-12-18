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
typedef  scalar_t__ GuiFont ;

/* Variables and functions */
 scalar_t__ NOFONT ; 
 int /*<<< orphan*/ * vim_strsave (int /*<<< orphan*/ *) ; 

char_u *
gui_mch_get_fontname(GuiFont font, char_u *name)
{
    if (font != NOFONT)
    {
        return vim_strsave((char_u*)font);
    }
    return NULL;
}