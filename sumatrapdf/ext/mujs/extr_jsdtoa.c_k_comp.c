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
 int D_1_LOG2_10 ; 
 int ceil (int) ; 

__attribute__((used)) static int k_comp(int e, int alpha, int gamma) {
	return ceil((alpha-e+63) * D_1_LOG2_10);
}