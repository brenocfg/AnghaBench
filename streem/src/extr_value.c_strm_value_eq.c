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
typedef  scalar_t__ strm_value ;
typedef  int /*<<< orphan*/  strm_cfunc ;

/* Variables and functions */
 int FALSE ; 
#define  STRM_TAG_ARRAY 133 
#define  STRM_TAG_CFUNC 132 
#define  STRM_TAG_PTR 131 
#define  STRM_TAG_STRING_F 130 
#define  STRM_TAG_STRING_O 129 
#define  STRM_TAG_STRUCT 128 
 int TRUE ; 
 int strm_ary_eq (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  strm_number_p (scalar_t__) ; 
 int strm_str_eq (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  strm_value_float (scalar_t__) ; 
 int strm_value_tag (scalar_t__) ; 
 int /*<<< orphan*/  strm_value_val (scalar_t__) ; 
 int /*<<< orphan*/  strm_value_vptr (scalar_t__) ; 

int
strm_value_eq(strm_value a, strm_value b)
{
  if (a == b) return TRUE;
  if (strm_value_tag(a) != strm_value_tag(b)) goto typediff;
  switch (strm_value_tag(a)) {
  case STRM_TAG_ARRAY:
  case STRM_TAG_STRUCT:
    return strm_ary_eq(a, b);
  case STRM_TAG_STRING_O:
  case STRM_TAG_STRING_F:
    return strm_str_eq(a, b);
  case STRM_TAG_CFUNC:
    return (strm_cfunc)(intptr_t)strm_value_val(a) == (strm_cfunc)(intptr_t)strm_value_val(b);
  case STRM_TAG_PTR:
    return strm_value_vptr(a) == strm_value_vptr(b);
  typediff:
  default:
    if (strm_number_p(a) && strm_number_p(b)) {
      return strm_value_float(a) == strm_value_float(b);
    }
    return FALSE;
  }
}