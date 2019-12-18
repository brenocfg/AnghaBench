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
typedef  int /*<<< orphan*/  bs_t ;

/* Variables and functions */
 int bs_read (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dirac_bool( bs_t *p_bs )
{
    return bs_read( p_bs, 1 );
}