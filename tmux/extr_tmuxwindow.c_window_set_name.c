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
struct window {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int VIS_CSTYLE ; 
 int VIS_NL ; 
 int VIS_OCTAL ; 
 int VIS_TAB ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notify_window (char*,struct window*) ; 
 int /*<<< orphan*/  utf8_stravis (int /*<<< orphan*/ *,char const*,int) ; 

void
window_set_name(struct window *w, const char *new_name)
{
	free(w->name);
	utf8_stravis(&w->name, new_name, VIS_OCTAL|VIS_CSTYLE|VIS_TAB|VIS_NL);
	notify_window("window-renamed", w);
}