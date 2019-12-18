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
 int /*<<< orphan*/  _test_fontfuncs_nil (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_font_funcs_get_empty () ; 
 int /*<<< orphan*/  hb_font_funcs_is_immutable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_fontfuncs_empty (void)
{
  g_assert (hb_font_funcs_get_empty ());
  g_assert (hb_font_funcs_is_immutable (hb_font_funcs_get_empty ()));
  _test_fontfuncs_nil (hb_font_funcs_get_empty ());
}