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
 int /*<<< orphan*/  HB_SCRIPT_ARABIC ; 
 int /*<<< orphan*/  HB_SCRIPT_COMMON ; 
 int /*<<< orphan*/  HB_SCRIPT_COPTIC ; 
 int /*<<< orphan*/  HB_SCRIPT_INHERITED ; 
 int /*<<< orphan*/  HB_SCRIPT_KATAKANA ; 
 int /*<<< orphan*/  HB_SCRIPT_LAO ; 
 int /*<<< orphan*/  HB_SCRIPT_LATIN ; 
 int /*<<< orphan*/  HB_SCRIPT_MANDAIC ; 
 int /*<<< orphan*/  HB_SCRIPT_MEETEI_MAYEK ; 
 int /*<<< orphan*/  HB_SCRIPT_NKO ; 
 int /*<<< orphan*/  HB_SCRIPT_UNKNOWN ; 
 int /*<<< orphan*/  HB_SCRIPT_VAI ; 
 int /*<<< orphan*/  HB_SCRIPT_YI ; 
 int /*<<< orphan*/  hb_script_from_string (char*,int) ; 
 int /*<<< orphan*/  test_simple_tags (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_ot_tag_script_simple (void)
{
  /* Arbitrary non-existent script */
  test_simple_tags ("wwyz", hb_script_from_string ("wWyZ", -1));

  /* These we don't really care about */
  test_simple_tags ("zyyy", HB_SCRIPT_COMMON);
  test_simple_tags ("zinh", HB_SCRIPT_INHERITED);
  test_simple_tags ("zzzz", HB_SCRIPT_UNKNOWN);

  test_simple_tags ("arab", HB_SCRIPT_ARABIC);
  test_simple_tags ("copt", HB_SCRIPT_COPTIC);
  test_simple_tags ("kana", HB_SCRIPT_KATAKANA);
  test_simple_tags ("latn", HB_SCRIPT_LATIN);

  /* These are trickier since their OT script tags have space. */
  test_simple_tags ("lao ", HB_SCRIPT_LAO);
  test_simple_tags ("yi  ", HB_SCRIPT_YI);
  /* Unicode-5.0 additions */
  test_simple_tags ("nko ", HB_SCRIPT_NKO);
  /* Unicode-5.1 additions */
  test_simple_tags ("vai ", HB_SCRIPT_VAI);

  /* https://docs.microsoft.com/en-us/typography/opentype/spec/scripttags */

  /* Unicode-5.2 additions */
  test_simple_tags ("mtei", HB_SCRIPT_MEETEI_MAYEK);
  /* Unicode-6.0 additions */
  test_simple_tags ("mand", HB_SCRIPT_MANDAIC);
}