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
typedef  int /*<<< orphan*/  spu_scale_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCALE_UNIT ; 
 int /*<<< orphan*/  spu_scale_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static spu_scale_t spu_scale_unit(void)
{
    return spu_scale_create(SCALE_UNIT, SCALE_UNIT);
}