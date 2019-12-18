#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__** spa_ddt; } ;
typedef  TYPE_1__ spa_t ;
typedef  enum zio_checksum { ____Placeholder_zio_checksum } zio_checksum ;
typedef  enum ddt_type { ____Placeholder_ddt_type } ddt_type ;
typedef  enum ddt_class { ____Placeholder_ddt_class } ddt_class ;
struct TYPE_5__ {int /*<<< orphan*/ ** ddt_histogram_cache; } ;
typedef  TYPE_2__ ddt_t ;
typedef  int /*<<< orphan*/  ddt_histogram_t ;

/* Variables and functions */
 int DDT_CLASSES ; 
 int DDT_TYPES ; 
 int ZIO_CHECKSUM_FUNCTIONS ; 
 int /*<<< orphan*/  ddt_histogram_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ddt_get_dedup_histogram(spa_t *spa, ddt_histogram_t *ddh)
{
	for (enum zio_checksum c = 0; c < ZIO_CHECKSUM_FUNCTIONS; c++) {
		ddt_t *ddt = spa->spa_ddt[c];
		for (enum ddt_type type = 0; type < DDT_TYPES; type++) {
			for (enum ddt_class class = 0; class < DDT_CLASSES;
			    class++) {
				ddt_histogram_add(ddh,
				    &ddt->ddt_histogram_cache[type][class]);
			}
		}
	}
}