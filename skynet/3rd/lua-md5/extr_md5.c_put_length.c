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
typedef  scalar_t__ WORD32 ;

/* Variables and functions */
 long MASK ; 

__attribute__((used)) static void put_length(WORD32 *x, long len) {
  /* in bits! */
  x[14] = (WORD32)((len<<3) & MASK);
  x[15] = (WORD32)(len>>(32-3) & 0x7);
}