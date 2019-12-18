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
 int post_solve_delay ; 
 int pre_solve_delay ; 
 int size ; 
 int solve_delay ; 

__attribute__((used)) static void SetDefaults()
{
    size = 10;
    pre_solve_delay = 5000;
    post_solve_delay = 5000;
    solve_delay = 1;
}