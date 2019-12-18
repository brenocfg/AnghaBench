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
 int /*<<< orphan*/  stb_easy_font_height (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb_easy_font_print (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb_easy_font_spacing (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb_easy_font_width (int /*<<< orphan*/ ) ; 

void ef_dummy(void)
{
   // suppress unsused-function warning
   stb_easy_font_spacing(0);
   stb_easy_font_print(0,0,0,0,0,0);
   stb_easy_font_width(0);
   stb_easy_font_height(0);
}