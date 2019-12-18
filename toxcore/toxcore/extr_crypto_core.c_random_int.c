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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  randnum ;

/* Variables and functions */
 int /*<<< orphan*/  randombytes (int /*<<< orphan*/ *,int) ; 

uint32_t random_int(void)
{
    uint32_t randnum;
    randombytes((uint8_t *)&randnum , sizeof(randnum));
    return randnum;
}