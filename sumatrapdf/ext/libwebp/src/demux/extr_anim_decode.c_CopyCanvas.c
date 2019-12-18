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
typedef  size_t uint64_t ;
typedef  size_t uint32_t ;

/* Variables and functions */
 size_t NUM_CHANNELS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int CopyCanvas(const uint8_t* src, uint8_t* dst,
                      uint32_t width, uint32_t height) {
  const uint64_t size = (uint64_t)width * height * NUM_CHANNELS;
  if (size != (size_t)size) return 0;
  assert(src != NULL && dst != NULL);
  memcpy(dst, src, (size_t)size);
  return 1;
}