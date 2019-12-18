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
 int /*<<< orphan*/  hb_face_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_set_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * hb_set_create () ; 
 int /*<<< orphan*/  hb_set_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_subset_test_check (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_subset_test_create_input (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_subset_test_create_subset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hb_subset_test_open_font (char*) ; 

__attribute__((used)) static void
test_subset_cmap_non_consecutive_glyphs (void)
{
  hb_face_t *face = hb_subset_test_open_font ("fonts/Roboto-Regular.D7,D8,D9,DA,DE.ttf");

  hb_set_t *codepoints = hb_set_create ();
  hb_face_t *face_subset;
  hb_set_add (codepoints, 0xD7);
  hb_set_add (codepoints, 0xD8);
  hb_set_add (codepoints, 0xD9);
  hb_set_add (codepoints, 0xDA);
  hb_set_add (codepoints, 0xDE);

  face_subset = hb_subset_test_create_subset (face, hb_subset_test_create_input (codepoints));
  hb_set_destroy (codepoints);

  hb_subset_test_check (face, face_subset, HB_TAG ('c','m','a','p'));

  hb_face_destroy (face_subset);
  hb_face_destroy (face);
}