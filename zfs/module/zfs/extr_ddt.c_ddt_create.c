#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * spa_ddt; int /*<<< orphan*/  spa_dedup_checksum; } ;
typedef  TYPE_1__ spa_t ;
typedef  enum zio_checksum { ____Placeholder_zio_checksum } zio_checksum ;

/* Variables and functions */
 int ZIO_CHECKSUM_FUNCTIONS ; 
 int /*<<< orphan*/  ZIO_DEDUPCHECKSUM ; 
 int /*<<< orphan*/  ddt_table_alloc (TYPE_1__*,int) ; 

void
ddt_create(spa_t *spa)
{
	spa->spa_dedup_checksum = ZIO_DEDUPCHECKSUM;

	for (enum zio_checksum c = 0; c < ZIO_CHECKSUM_FUNCTIONS; c++)
		spa->spa_ddt[c] = ddt_table_alloc(spa, c);
}