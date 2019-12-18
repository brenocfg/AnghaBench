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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static void AddSingle(uint32_t p,
                      uint32_t* const a, uint32_t* const r,
                      uint32_t* const g, uint32_t* const b) {
  ++a[(p >> 24) & 0xff];
  ++r[(p >> 16) & 0xff];
  ++g[(p >>  8) & 0xff];
  ++b[(p >>  0) & 0xff];
}