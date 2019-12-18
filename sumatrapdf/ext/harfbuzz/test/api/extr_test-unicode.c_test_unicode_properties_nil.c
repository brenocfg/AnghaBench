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
typedef  int /*<<< orphan*/  hb_unicode_funcs_t ;

/* Variables and functions */
 int /*<<< orphan*/  _test_unicode_properties_nil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_assert (int) ; 
 int /*<<< orphan*/ * hb_unicode_funcs_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_unicode_funcs_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_unicode_funcs_is_immutable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_unicode_properties_nil (void)
{
  hb_unicode_funcs_t *uf = hb_unicode_funcs_create (NULL);

  g_assert (!hb_unicode_funcs_is_immutable (uf));
  _test_unicode_properties_nil (uf);

  hb_unicode_funcs_destroy (uf);
}