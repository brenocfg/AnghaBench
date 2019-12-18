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
typedef  int /*<<< orphan*/  hb_tag_t ;
typedef  int /*<<< orphan*/  hb_face_t ;
typedef  int /*<<< orphan*/  hb_blob_t ;

/* Variables and functions */
 int HB_UNTAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hb_blob_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_face_reference_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_test_assert_blobs_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static inline void
hb_subset_test_check (hb_face_t *expected,
                      hb_face_t *actual,
                      hb_tag_t   table)
{
  hb_blob_t *expected_blob, *actual_blob;
  fprintf(stderr, "compare %c%c%c%c\n", HB_UNTAG(table));
  expected_blob = hb_face_reference_table (expected, table);
  actual_blob = hb_face_reference_table (actual, table);
  hb_test_assert_blobs_equal (expected_blob, actual_blob);
  hb_blob_destroy (expected_blob);
  hb_blob_destroy (actual_blob);
}