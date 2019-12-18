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
struct strm_string {char const* ptr; } ;
typedef  int /*<<< orphan*/  strm_string ;

/* Variables and functions */
#define  STRM_TAG_STRING_6 131 
#define  STRM_TAG_STRING_F 130 
#define  STRM_TAG_STRING_I 129 
#define  STRM_TAG_STRING_O 128 
 char const* VALP_PTR (int /*<<< orphan*/ *) ; 
 int strm_value_tag (int /*<<< orphan*/ ) ; 
 scalar_t__ strm_value_vptr (int /*<<< orphan*/ ) ; 

const char*
strm_strp_ptr(strm_string* s)
{
  switch (strm_value_tag(*s)) {
  case STRM_TAG_STRING_I:
    return VALP_PTR(s)+1;
  case STRM_TAG_STRING_6:
    return VALP_PTR(s);
  case STRM_TAG_STRING_O:
  case STRM_TAG_STRING_F:
    {
      struct strm_string* str = (struct strm_string*)strm_value_vptr(*s);
      return str->ptr;
    }
  default:
    return NULL;
  }
}