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

/* Variables and functions */
 int CMP (unsigned int const,unsigned int const) ; 

__attribute__((used)) static int unsigned_compare(const unsigned *a, const unsigned *b) {
        return CMP(*a, *b);
}