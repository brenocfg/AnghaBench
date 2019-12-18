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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int fwrite (scalar_t__*,int,int,int /*<<< orphan*/ * const) ; 

__attribute__((used)) static int WriteLE(FILE* const out, uint32_t val, int num) {
  uint8_t buf[4];
  int i;
  for (i = 0; i < num; ++i) {
    buf[i] = (uint8_t)(val & 0xff);
    val >>= 8;
  }
  return (fwrite(buf, num, 1, out) == 1);
}