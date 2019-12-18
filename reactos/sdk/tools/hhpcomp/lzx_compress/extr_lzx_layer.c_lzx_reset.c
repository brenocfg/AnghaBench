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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int need_1bit_header; int R0; int R1; int R2; int main_tree_size; int /*<<< orphan*/  lzi; int /*<<< orphan*/  prev_length_treelengths; int /*<<< orphan*/  prev_main_treelengths; } ;
typedef  TYPE_1__ lzx_data ;

/* Variables and functions */
 int NUM_SECONDARY_LENGTHS ; 
 int /*<<< orphan*/  lz_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void 
lzx_reset(lzx_data *lzxd)
{
  lzxd->need_1bit_header = 1;
  lzxd->R0 = lzxd->R1 = lzxd->R2 = 1;
  memset(lzxd->prev_main_treelengths, 0, lzxd->main_tree_size * sizeof(uint8_t));
  memset(lzxd->prev_length_treelengths, 0, NUM_SECONDARY_LENGTHS * sizeof(uint8_t));
  lz_reset(lzxd->lzi);
}