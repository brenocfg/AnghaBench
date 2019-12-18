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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 scalar_t__ WebPHasAlpha32b (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ WebPHasAlpha8b (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  WebPInitAlphaProcessing () ; 

__attribute__((used)) static int CheckNonOpaque(const uint8_t* alpha, int width, int height,
                          int x_step, int y_step) {
  if (alpha == NULL) return 0;
  WebPInitAlphaProcessing();
  if (x_step == 1) {
    for (; height-- > 0; alpha += y_step) {
      if (WebPHasAlpha8b(alpha, width)) return 1;
    }
  } else {
    for (; height-- > 0; alpha += y_step) {
      if (WebPHasAlpha32b(alpha, width)) return 1;
    }
  }
  return 0;
}