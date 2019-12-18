#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_t ;
struct TYPE_10__ {int /*<<< orphan*/  vdev_spa; TYPE_1__* vdev_ops; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int /*<<< orphan*/  abd_t ;
struct TYPE_9__ {int vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int SCL_L2ARC ; 
 scalar_t__ SCL_STATE ; 
 int SCL_ZIO ; 
 int VDEV_LABELS ; 
 int VDEV_UBERBLOCK_COUNT (TYPE_2__*) ; 
 int /*<<< orphan*/  VDEV_UBERBLOCK_OFFSET (TYPE_2__*,int) ; 
 int /*<<< orphan*/  VDEV_UBERBLOCK_SIZE (TYPE_2__*) ; 
 int ZIO_FLAG_CANFAIL ; 
 int ZIO_FLAG_CONFIG_WRITER ; 
 int ZIO_FLAG_DONT_PROPAGATE ; 
 int ZIO_FLAG_SPECULATIVE ; 
 int /*<<< orphan*/ * abd_alloc_linear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abd_to_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abd_zero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_enter (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_config_held (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ uberblock_verify (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_label_read (int /*<<< orphan*/ *,TYPE_2__*,int const,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vdev_label_write (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * zio_root (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ zio_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vdev_copy_uberblocks(vdev_t *vd)
{
	abd_t *ub_abd;
	zio_t *write_zio;
	int locks = (SCL_L2ARC | SCL_ZIO);
	int flags = ZIO_FLAG_CONFIG_WRITER | ZIO_FLAG_CANFAIL |
	    ZIO_FLAG_SPECULATIVE;

	ASSERT(spa_config_held(vd->vdev_spa, SCL_STATE, RW_READER) ==
	    SCL_STATE);
	ASSERT(vd->vdev_ops->vdev_op_leaf);

	spa_config_enter(vd->vdev_spa, locks, FTAG, RW_READER);

	ub_abd = abd_alloc_linear(VDEV_UBERBLOCK_SIZE(vd), B_TRUE);

	write_zio = zio_root(vd->vdev_spa, NULL, NULL, flags);
	for (int n = 0; n < VDEV_UBERBLOCK_COUNT(vd); n++) {
		const int src_label = 0;
		zio_t *zio;

		zio = zio_root(vd->vdev_spa, NULL, NULL, flags);
		vdev_label_read(zio, vd, src_label, ub_abd,
		    VDEV_UBERBLOCK_OFFSET(vd, n), VDEV_UBERBLOCK_SIZE(vd),
		    NULL, NULL, flags);

		if (zio_wait(zio) || uberblock_verify(abd_to_buf(ub_abd)))
			abd_zero(ub_abd, VDEV_UBERBLOCK_SIZE(vd));

		for (int l = 2; l < VDEV_LABELS; l++)
			vdev_label_write(write_zio, vd, l, ub_abd,
			    VDEV_UBERBLOCK_OFFSET(vd, n),
			    VDEV_UBERBLOCK_SIZE(vd), NULL, NULL,
			    flags | ZIO_FLAG_DONT_PROPAGATE);
	}
	(void) zio_wait(write_zio);

	spa_config_exit(vd->vdev_spa, locks, FTAG);

	abd_free(ub_abd);
}