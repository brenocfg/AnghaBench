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
typedef  int /*<<< orphan*/  const uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  const GetLE32 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static uint32_t ReadLE32(const uint8_t** data) {
  const uint32_t val = GetLE32(*data);
  *data += 4;
  return val;
}