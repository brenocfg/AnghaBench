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
typedef  int uint8_t ;

/* Variables and functions */

int VP8CheckSignature(const uint8_t* const data, size_t data_size) {
  return (data_size >= 3 &&
          data[0] == 0x9d && data[1] == 0x01 && data[2] == 0x2a);
}