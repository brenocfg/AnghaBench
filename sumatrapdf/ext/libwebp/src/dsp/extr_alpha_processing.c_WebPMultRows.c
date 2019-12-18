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
 int /*<<< orphan*/  WebPMultRow (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int) ; 

void WebPMultRows(uint8_t* ptr, int stride,
                  const uint8_t* alpha, int alpha_stride,
                  int width, int num_rows, int inverse) {
  int n;
  for (n = 0; n < num_rows; ++n) {
    WebPMultRow(ptr, alpha, width, inverse);
    ptr += stride;
    alpha += alpha_stride;
  }
}