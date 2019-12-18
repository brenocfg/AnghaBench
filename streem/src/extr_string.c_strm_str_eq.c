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
typedef  scalar_t__ strm_string ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ STRM_TAG_STRING_F ; 
 int TRUE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strm_str_len (scalar_t__) ; 
 int /*<<< orphan*/  strm_str_ptr (scalar_t__) ; 
 scalar_t__ strm_value_tag (scalar_t__) ; 

int
strm_str_eq(strm_string a, strm_string b)
{
  if (a == b) return TRUE;
  if (strm_value_tag(a) == STRM_TAG_STRING_F &&
      strm_value_tag(b) == STRM_TAG_STRING_F) {
    /* pointer comparison is OK if strings are interned */
    return FALSE;
  }
  if (strm_str_len(a) != strm_str_len(b)) return FALSE;
  if (memcmp(strm_str_ptr(a), strm_str_ptr(b), strm_str_len(a)) == 0)
    return TRUE;
  return FALSE;
}