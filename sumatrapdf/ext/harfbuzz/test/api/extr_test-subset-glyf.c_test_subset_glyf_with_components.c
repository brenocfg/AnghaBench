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
 int /*<<< orphan*/  check_maxp_num_glyphs (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  hb_face_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_set_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * hb_set_create () ; 
 int /*<<< orphan*/  hb_set_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_subset_test_check (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_subset_test_create_input (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_subset_test_create_subset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hb_subset_test_open_font (char*) ; 

__attribute__((used)) static void
test_subset_glyf_with_components (void)
{
  hb_face_t *face_components = hb_subset_test_open_font ("fonts/Roboto-Regular.components.ttf");
  hb_face_t *face_subset = hb_subset_test_open_font ("fonts/Roboto-Regular.components.subset.ttf");

  hb_set_t *codepoints = hb_set_create();
  hb_face_t *face_generated_subset;
  hb_set_add (codepoints, 0x1fc);
  face_generated_subset = hb_subset_test_create_subset (face_components, hb_subset_test_create_input (codepoints));
  hb_set_destroy (codepoints);

  hb_subset_test_check (face_subset, face_generated_subset, HB_TAG ('g','l','y','f'));
  hb_subset_test_check (face_subset, face_generated_subset, HB_TAG ('l','o','c', 'a'));
  check_maxp_num_glyphs(face_generated_subset, 4, true);

  hb_face_destroy (face_generated_subset);
  hb_face_destroy (face_subset);
  hb_face_destroy (face_components);
}