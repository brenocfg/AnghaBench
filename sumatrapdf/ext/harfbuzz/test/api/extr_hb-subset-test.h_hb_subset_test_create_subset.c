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
typedef  int /*<<< orphan*/  hb_subset_input_t ;
typedef  int /*<<< orphan*/  hb_face_t ;

/* Variables and functions */
 int /*<<< orphan*/  g_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_subset (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_subset_input_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline hb_face_t *
hb_subset_test_create_subset (hb_face_t *source,
                              hb_subset_input_t *input)
{
  hb_face_t *subset = hb_subset (source, input);
  g_assert (subset);

  hb_subset_input_destroy (input);
  return subset;
}