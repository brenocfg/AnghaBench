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
 int /*<<< orphan*/  hb_test_add (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_test_init (int*,char***) ; 
 int hb_test_run () ; 
 int /*<<< orphan*/  test_face_create ; 
 int /*<<< orphan*/  test_face_createfortables ; 
 int /*<<< orphan*/  test_face_empty ; 
 int /*<<< orphan*/  test_font_empty ; 
 int /*<<< orphan*/  test_font_properties ; 
 int /*<<< orphan*/  test_fontfuncs_empty ; 
 int /*<<< orphan*/  test_fontfuncs_nil ; 
 int /*<<< orphan*/  test_fontfuncs_subclassing ; 

int
main (int argc, char **argv)
{
  hb_test_init (&argc, &argv);

  hb_test_add (test_face_empty);
  hb_test_add (test_face_create);
  hb_test_add (test_face_createfortables);

  hb_test_add (test_fontfuncs_empty);
  hb_test_add (test_fontfuncs_nil);
  hb_test_add (test_fontfuncs_subclassing);

  hb_test_add (test_font_empty);
  hb_test_add (test_font_properties);

  return hb_test_run();
}