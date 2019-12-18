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
typedef  int /*<<< orphan*/  VP8BitWriter ;

/* Variables and functions */
 scalar_t__ VP8PutBit (int /*<<< orphan*/ * const,int,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void PutSegment(VP8BitWriter* const bw, int s, const uint8_t* p) {
  if (VP8PutBit(bw, s >= 2, p[0])) p += 1;
  VP8PutBit(bw, s & 1, p[1]);
}