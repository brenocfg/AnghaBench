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

/* Variables and functions */
 int FALSE ; 
#define  STRM_TAG_ARRAY 129 
#define  STRM_TAG_STRUCT 128 
 int TRUE ; 
 int strm_value_tag (int /*<<< orphan*/ ) ; 

int
strm_array_p(strm_value v)
{
  switch (strm_value_tag(v)) {
  case STRM_TAG_ARRAY:
  case STRM_TAG_STRUCT:
    return TRUE;
  default:
    return FALSE;
  }
}