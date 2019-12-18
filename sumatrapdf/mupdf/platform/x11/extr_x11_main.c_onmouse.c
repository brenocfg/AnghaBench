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
 scalar_t__ advance_scheduled ; 
 int /*<<< orphan*/  gapp ; 
 scalar_t__ justcopied ; 
 int /*<<< orphan*/  pdfapp_onmouse (int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int /*<<< orphan*/  winrepaint (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void onmouse(int x, int y, int btn, int modifiers, int state)
{
	if (state != 0)
		advance_scheduled = 0;

	if (state != 0 && justcopied)
	{
		justcopied = 0;
		winrepaint(&gapp);
	}

	pdfapp_onmouse(&gapp, x, y, btn, modifiers, state);
}