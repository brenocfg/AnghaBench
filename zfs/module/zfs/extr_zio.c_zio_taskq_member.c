#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t zio_type_t ;
typedef  size_t zio_taskq_type_t ;
struct TYPE_5__ {TYPE_3__* io_spa; int /*<<< orphan*/ * io_executor; } ;
typedef  TYPE_1__ zio_t ;
typedef  size_t uint_t ;
struct TYPE_6__ {size_t stqs_count; int /*<<< orphan*/ * stqs_taskq; } ;
typedef  TYPE_2__ spa_taskqs_t ;
struct TYPE_7__ {TYPE_2__** spa_zio_taskq; } ;
typedef  TYPE_3__ spa_t ;
typedef  int /*<<< orphan*/  kthread_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 size_t ZIO_TYPES ; 
 scalar_t__ taskq_member (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static boolean_t
zio_taskq_member(zio_t *zio, zio_taskq_type_t q)
{
	kthread_t *executor = zio->io_executor;
	spa_t *spa = zio->io_spa;

	for (zio_type_t t = 0; t < ZIO_TYPES; t++) {
		spa_taskqs_t *tqs = &spa->spa_zio_taskq[t][q];
		uint_t i;
		for (i = 0; i < tqs->stqs_count; i++) {
			if (taskq_member(tqs->stqs_taskq[i], executor))
				return (B_TRUE);
		}
	}

	return (B_FALSE);
}