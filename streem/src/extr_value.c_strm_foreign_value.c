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
 int STRM_TAG_FOREIGN ; 
 int STRM_VAL_MASK ; 

strm_value
strm_foreign_value(void* p)
{
  return STRM_TAG_FOREIGN | ((strm_value)(intptr_t)p & STRM_VAL_MASK);
}