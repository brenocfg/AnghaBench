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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  HorizontalUnfilter_C (int /*<<< orphan*/ *,scalar_t__ const*,scalar_t__*,int) ; 

__attribute__((used)) static void VerticalUnfilter_C(const uint8_t* prev, const uint8_t* in,
                               uint8_t* out, int width) {
  if (prev == NULL) {
    HorizontalUnfilter_C(NULL, in, out, width);
  } else {
    int i;
    for (i = 0; i < width; ++i) out[i] = (uint8_t)(prev[i] + in[i]);
  }
}