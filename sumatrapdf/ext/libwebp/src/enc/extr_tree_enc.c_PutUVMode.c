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
typedef  int /*<<< orphan*/  VP8BitWriter ;

/* Variables and functions */
 int DC_PRED ; 
 int H_PRED ; 
 scalar_t__ VP8PutBit (int /*<<< orphan*/ * const,int,int) ; 
 int V_PRED ; 

__attribute__((used)) static void PutUVMode(VP8BitWriter* const bw, int uv_mode) {
  if (VP8PutBit(bw, uv_mode != DC_PRED, 142)) {
    if (VP8PutBit(bw, uv_mode != V_PRED, 114)) {
      VP8PutBit(bw, uv_mode != H_PRED, 183);    // else: TM_PRED
    }
  }
}