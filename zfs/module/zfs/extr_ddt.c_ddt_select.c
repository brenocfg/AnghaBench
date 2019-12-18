#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ ** spa_ddt; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  ddt_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 size_t BP_GET_CHECKSUM (int /*<<< orphan*/  const*) ; 

ddt_t *
ddt_select(spa_t *spa, const blkptr_t *bp)
{
	return (spa->spa_ddt[BP_GET_CHECKSUM(bp)]);
}