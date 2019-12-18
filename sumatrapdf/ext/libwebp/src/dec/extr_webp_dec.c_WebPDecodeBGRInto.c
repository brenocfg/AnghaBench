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
 int /*<<< orphan*/ * DecodeIntoRGBABuffer (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  MODE_BGR ; 

uint8_t* WebPDecodeBGRInto(const uint8_t* data, size_t data_size,
                           uint8_t* output, size_t size, int stride) {
  return DecodeIntoRGBABuffer(MODE_BGR, data, data_size, output, stride, size);
}