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
 int /*<<< orphan*/  DoHorizontalFilter_C (int /*<<< orphan*/  const*,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void HorizontalFilter_C(const uint8_t* data, int width, int height,
                               int stride, uint8_t* filtered_data) {
  DoHorizontalFilter_C(data, width, height, stride, 0, height, 0,
                       filtered_data);
}