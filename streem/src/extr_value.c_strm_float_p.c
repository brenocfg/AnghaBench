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
typedef  int strm_value ;

/* Variables and functions */
 int STRM_TAG_NAN ; 

int
strm_float_p(strm_value v)
{
  /* confirm for nan/+inf/-inf */
  return v == STRM_TAG_NAN || (v & STRM_TAG_NAN) != STRM_TAG_NAN;
}