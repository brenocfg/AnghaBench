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

/* Variables and functions */
 int B_DC_PRED ; 
 int B_DC_PRED_NOLEFT ; 
 int B_DC_PRED_NOTOP ; 
 int B_DC_PRED_NOTOPLEFT ; 

__attribute__((used)) static int CheckMode(int mb_x, int mb_y, int mode) {
  if (mode == B_DC_PRED) {
    if (mb_x == 0) {
      return (mb_y == 0) ? B_DC_PRED_NOTOPLEFT : B_DC_PRED_NOLEFT;
    } else {
      return (mb_y == 0) ? B_DC_PRED_NOTOP : B_DC_PRED;
    }
  }
  return mode;
}