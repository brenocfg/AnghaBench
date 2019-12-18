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
typedef  int /*<<< orphan*/  gconstpointer ;

/* Variables and functions */
 int /*<<< orphan*/  data_fixture ; 
 int /*<<< orphan*/  hb_glib_get_unicode_funcs () ; 
 int /*<<< orphan*/  hb_icu_get_unicode_funcs () ; 
 int /*<<< orphan*/  hb_test_add (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_test_add_data_flavor (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_test_add_fixture (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_test_init (int*,char***) ; 
 int hb_test_run () ; 
 int /*<<< orphan*/  hb_unicode_funcs_get_default () ; 
 scalar_t__ script_roundtrip_default ; 
 scalar_t__ script_roundtrip_glib ; 
 scalar_t__ script_roundtrip_icu ; 
 int /*<<< orphan*/  test_unicode_chainup ; 
 int /*<<< orphan*/  test_unicode_normalization ; 
 int /*<<< orphan*/  test_unicode_properties ; 
 int /*<<< orphan*/  test_unicode_properties_empty ; 
 int /*<<< orphan*/  test_unicode_properties_nil ; 
 int /*<<< orphan*/  test_unicode_script_roundtrip ; 
 int /*<<< orphan*/  test_unicode_setters ; 
 int /*<<< orphan*/  test_unicode_subclassing_deep ; 
 int /*<<< orphan*/  test_unicode_subclassing_default ; 
 int /*<<< orphan*/  test_unicode_subclassing_nil ; 

int
main (int argc, char **argv)
{
  hb_test_init (&argc, &argv);

  hb_test_add (test_unicode_properties_nil);
  hb_test_add (test_unicode_properties_empty);

  hb_test_add_data_flavor (hb_unicode_funcs_get_default (),          "default", test_unicode_properties);
  hb_test_add_data_flavor (hb_unicode_funcs_get_default (),          "default", test_unicode_normalization);
  hb_test_add_data_flavor ((gconstpointer) script_roundtrip_default, "default", test_unicode_script_roundtrip);
#ifdef HAVE_GLIB
  hb_test_add_data_flavor (hb_glib_get_unicode_funcs (),             "glib",    test_unicode_properties);
  hb_test_add_data_flavor (hb_glib_get_unicode_funcs (),             "glib",    test_unicode_normalization);
  hb_test_add_data_flavor ((gconstpointer) script_roundtrip_glib,    "glib",    test_unicode_script_roundtrip);
#endif
#ifdef HAVE_ICU
  hb_test_add_data_flavor (hb_icu_get_unicode_funcs (),              "icu",     test_unicode_properties);
  hb_test_add_data_flavor (hb_icu_get_unicode_funcs (),              "icu",     test_unicode_normalization);
  hb_test_add_data_flavor ((gconstpointer) script_roundtrip_icu,     "icu",     test_unicode_script_roundtrip);
#endif

  hb_test_add (test_unicode_chainup);

  hb_test_add (test_unicode_setters);

  hb_test_add_fixture (data_fixture, NULL, test_unicode_subclassing_nil);
  hb_test_add_fixture (data_fixture, NULL, test_unicode_subclassing_default);
  hb_test_add_fixture (data_fixture, NULL, test_unicode_subclassing_deep);

  return hb_test_run ();
}