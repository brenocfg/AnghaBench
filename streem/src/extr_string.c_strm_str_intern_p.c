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
typedef  int /*<<< orphan*/  strm_string ;

/* Variables and functions */
 int FALSE ; 
#define  STRM_TAG_STRING_6 131 
#define  STRM_TAG_STRING_F 130 
#define  STRM_TAG_STRING_I 129 
#define  STRM_TAG_STRING_O 128 
 int TRUE ; 
 int strm_value_tag (int /*<<< orphan*/ ) ; 

int
strm_str_intern_p(strm_string s)
{
  switch (strm_value_tag(s)) {
  case STRM_TAG_STRING_I:
  case STRM_TAG_STRING_6:
  case STRM_TAG_STRING_F:
    return TRUE;
  case STRM_TAG_STRING_O:
  default:
    return FALSE;
  }
}