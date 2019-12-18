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
struct TYPE_3__ {int /*<<< orphan*/  argb_; } ;
typedef  TYPE_1__ VP8LEncoder ;
typedef  int /*<<< orphan*/  VP8LBitWriter ;

/* Variables and functions */
 int /*<<< orphan*/  SUBTRACT_GREEN ; 
 int /*<<< orphan*/  TRANSFORM_PRESENT ; 
 int /*<<< orphan*/  VP8LPutBits (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VP8LSubtractGreenFromBlueAndRed (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ApplySubtractGreen(VP8LEncoder* const enc, int width, int height,
                               VP8LBitWriter* const bw) {
  VP8LPutBits(bw, TRANSFORM_PRESENT, 1);
  VP8LPutBits(bw, SUBTRACT_GREEN, 2);
  VP8LSubtractGreenFromBlueAndRed(enc->argb_, width * height);
}