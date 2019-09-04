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
typedef  double LONG ;
typedef  double FLOAT ;

/* Variables and functions */

__attribute__((used)) static inline FLOAT twips_to_points(LONG value)
{
    return value * 72.0 / 1440;
}