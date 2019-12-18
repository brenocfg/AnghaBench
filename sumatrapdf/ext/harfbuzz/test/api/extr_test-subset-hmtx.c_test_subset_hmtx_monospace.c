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
 int /*<<< orphan*/  check_num_hmetrics (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hb_face_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_set_add (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/ * hb_set_create () ; 
 int /*<<< orphan*/  hb_set_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_subset_test_check (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_subset_test_create_input (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_subset_test_create_subset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hb_subset_test_open_font (char*) ; 

__attribute__((used)) static void
test_subset_hmtx_monospace (void)
{
  hb_face_t *face_abc = hb_subset_test_open_font ("fonts/Inconsolata-Regular.abc.ttf");
  hb_face_t *face_ac = hb_subset_test_open_font ("fonts/Inconsolata-Regular.ac.ttf");

  hb_set_t *codepoints = hb_set_create ();
  hb_face_t *face_abc_subset;
  hb_set_add (codepoints, 'a');
  hb_set_add (codepoints, 'c');
  face_abc_subset = hb_subset_test_create_subset (face_abc, hb_subset_test_create_input (codepoints));
  hb_set_destroy (codepoints);

  check_num_hmetrics(face_abc_subset, 1); /* everything has same width */
  hb_subset_test_check (face_ac, face_abc_subset, HB_TAG ('h','m','t','x'));

  hb_face_destroy (face_abc_subset);
  hb_face_destroy (face_abc);
  hb_face_destroy (face_ac);
}