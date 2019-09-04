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
typedef  int increment_t ;

/* Variables and functions */
 int SHIFT_BITS ; 

__attribute__((used)) static inline increment_t
int_to_fp (int x)
{	return (((increment_t) (x)) << SHIFT_BITS) ;
}