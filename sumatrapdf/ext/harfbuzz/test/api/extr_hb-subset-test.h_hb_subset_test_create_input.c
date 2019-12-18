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
typedef  int /*<<< orphan*/  hb_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_set_union (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * hb_subset_input_create_or_fail () ; 
 int /*<<< orphan*/ * hb_subset_input_unicode_set (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline hb_subset_input_t *
hb_subset_test_create_input(const hb_set_t  *codepoints)
{
  hb_subset_input_t *input = hb_subset_input_create_or_fail ();
  hb_set_t * input_codepoints = hb_subset_input_unicode_set (input);
  hb_set_union (input_codepoints, codepoints);
  return input;
}