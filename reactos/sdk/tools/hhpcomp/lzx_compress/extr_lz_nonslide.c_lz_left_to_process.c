#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int chars_in_buf; int block_loc; } ;
typedef  TYPE_1__ lz_info ;

/* Variables and functions */

int lz_left_to_process(lz_info *lzi)
{
  return lzi->chars_in_buf - lzi->block_loc;
}