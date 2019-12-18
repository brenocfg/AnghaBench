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
 scalar_t__ STRM_TAG_PTR ; 
 scalar_t__ strm_value_tag (int /*<<< orphan*/ ) ; 
 scalar_t__ strm_value_val (int /*<<< orphan*/ ) ; 

int
strm_nil_p(strm_value v)
{
  if (strm_value_tag(v) != STRM_TAG_PTR)
    return FALSE;
  return strm_value_val(v) == 0;
}