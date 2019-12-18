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
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
#define  STRM_TAG_INT 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  strm_float_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_to_float (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_to_int (int /*<<< orphan*/ ) ; 
 int const strm_value_tag (int /*<<< orphan*/ ) ; 

int32_t
strm_value_int(strm_value v)
{
  switch (strm_value_tag(v)) {
  case STRM_TAG_INT:
    return strm_to_int(v);
  default:
    if (strm_float_p(v))
      return strm_to_float(v);
    assert(strm_value_tag(v) == STRM_TAG_INT);
    break;
  }
  /* not reached */
  return 0;
}