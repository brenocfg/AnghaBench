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
typedef  int /*<<< orphan*/ * hb_language_t ;

/* Variables and functions */
 int /*<<< orphan*/ * HB_LANGUAGE_INVALID ; 
 int /*<<< orphan*/  g_assert (int) ; 
 int /*<<< orphan*/ * hb_language_from_string (char*,int) ; 
 int /*<<< orphan*/ * hb_language_get_default () ; 
 int /*<<< orphan*/ * hb_language_to_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_types_language (void)
{
  hb_language_t fa = hb_language_from_string ("fa", -1);
  hb_language_t fa_IR = hb_language_from_string ("fa_IR", -1);
  hb_language_t fa_ir = hb_language_from_string ("fa-ir", -1);
  hb_language_t en = hb_language_from_string ("en", -1);

  g_assert (HB_LANGUAGE_INVALID == NULL);

  g_assert (fa != NULL);
  g_assert (fa_IR != NULL);
  g_assert (fa_IR == fa_ir);

  g_assert (en != NULL);
  g_assert (en != fa);

  /* Test recall */
  g_assert (en == hb_language_from_string ("en", -1));
  g_assert (en == hb_language_from_string ("eN", -1));
  g_assert (en == hb_language_from_string ("Enx", 2));

  g_assert (HB_LANGUAGE_INVALID == hb_language_from_string (NULL, -1));
  g_assert (HB_LANGUAGE_INVALID == hb_language_from_string ("", -1));
  g_assert (HB_LANGUAGE_INVALID == hb_language_from_string ("en", 0));
  g_assert (HB_LANGUAGE_INVALID != hb_language_from_string ("en", 1));
  g_assert (NULL == hb_language_to_string (HB_LANGUAGE_INVALID));

  /* Not sure how to test this better.  Setting env vars
   * here doesn't sound like the right approach, and I'm
   * not sure that it even works. */
  g_assert (HB_LANGUAGE_INVALID != hb_language_get_default ());
}