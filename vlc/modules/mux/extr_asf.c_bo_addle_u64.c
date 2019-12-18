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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  bo_t ;

/* Variables and functions */
 int /*<<< orphan*/  bo_addle_u32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void bo_addle_u64( bo_t *p_bo, uint64_t i )
{
    bo_addle_u32( p_bo, i &0xffffffff );
    bo_addle_u32( p_bo, ( ( i >> 32) &0xffffffff ) );
}