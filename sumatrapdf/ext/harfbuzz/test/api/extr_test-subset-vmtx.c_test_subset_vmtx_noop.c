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
typedef  int /*<<< orphan*/  hb_set_t ;
typedef  int /*<<< orphan*/  hb_face_t ;

/* Variables and functions */
 int /*<<< orphan*/  HB_TAG (char,char,char,char) ; 
 int /*<<< orphan*/  check_num_vmetrics (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hb_face_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_set_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * hb_set_create () ; 
 int /*<<< orphan*/  hb_set_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_subset_test_check (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_subset_test_create_input (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_subset_test_create_subset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hb_subset_test_open_font (char*) ; 

__attribute__((used)) static void
test_subset_vmtx_noop (void)
{
  hb_face_t *face_full = hb_subset_test_open_font ("fonts/Mplus1p-Regular.660E,6975,73E0,5EA6,8F38,6E05.ttf");

  hb_set_t *codepoints = hb_set_create();
  hb_set_add (codepoints, 0x660E);
  hb_set_add (codepoints, 0x6975);
  hb_set_add (codepoints, 0x73E0);
  hb_set_add (codepoints, 0x5EA6);
  hb_set_add (codepoints, 0x8F38);
  hb_set_add (codepoints, 0x6E05);
  hb_face_t *face_full_subset = hb_subset_test_create_subset (face_full, hb_subset_test_create_input (codepoints));
  hb_set_destroy (codepoints);

  check_num_vmetrics(face_full_subset, 1); /* all have the same width */
  hb_subset_test_check (face_full, face_full_subset, HB_TAG ('v','m','t','x'));

  hb_face_destroy (face_full_subset);
  hb_face_destroy (face_full);
}