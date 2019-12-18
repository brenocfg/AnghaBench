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
typedef  int /*<<< orphan*/  Window ;
struct TYPE_4__ {int /*<<< orphan*/  utf8_string_atom; int /*<<< orphan*/  name_atom; } ;
struct TYPE_5__ {TYPE_1__ ewmhints; int /*<<< orphan*/  display; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  PropModeReplace ; 
 int /*<<< orphan*/  XChangeProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int strlen (char const*) ; 

void
ewmh_set_wm_name(RDPCLIENT * This, Window wnd, const char *title)
{
	int len;

	len = strlen(title);
	XChangeProperty(This->display, wnd, This->ewmhints.name_atom, This->ewmhints.utf8_string_atom,
			8, PropModeReplace, (unsigned char *) title, len);
}