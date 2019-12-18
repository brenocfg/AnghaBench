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
typedef  int /*<<< orphan*/  zbookmark_phys_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int SPA_MINBLOCKSHIFT ; 
 int /*<<< orphan*/  create_zbookmark_from_obj_off (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zbookmark_compare (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
redact_range_compare(uint64_t obj1, uint64_t off1, uint32_t dbss1,
    uint64_t obj2, uint64_t off2, uint32_t dbss2)
{
	zbookmark_phys_t z1, z2;
	create_zbookmark_from_obj_off(&z1, obj1, off1);
	create_zbookmark_from_obj_off(&z2, obj2, off2);

	return (zbookmark_compare(dbss1 >> SPA_MINBLOCKSHIFT, 0,
	    dbss2 >> SPA_MINBLOCKSHIFT, 0, &z1, &z2));
}