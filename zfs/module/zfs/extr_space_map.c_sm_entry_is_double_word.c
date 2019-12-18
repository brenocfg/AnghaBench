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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ SM2_PREFIX ; 
 scalar_t__ SM_PREFIX_DECODE (int /*<<< orphan*/ ) ; 

boolean_t
sm_entry_is_double_word(uint64_t e)
{
	return (SM_PREFIX_DECODE(e) == SM2_PREFIX);
}