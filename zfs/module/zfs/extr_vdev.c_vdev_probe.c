#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int io_flags; } ;
typedef  TYPE_2__ zio_t ;
struct TYPE_21__ {int /*<<< orphan*/  vdev_psize; int /*<<< orphan*/  vdev_probe_lock; int /*<<< orphan*/  vdev_probe_wanted; TYPE_2__* vdev_probe_zio; void* vdev_cant_write; void* vdev_cant_read; TYPE_1__* vdev_ops; int /*<<< orphan*/ * vdev_spa; } ;
typedef  TYPE_3__ vdev_t ;
struct TYPE_22__ {int vps_flags; } ;
typedef  TYPE_4__ vdev_probe_stats_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_19__ {int /*<<< orphan*/  vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 void* B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SCL_ZIO ; 
 int /*<<< orphan*/  SPA_ASYNC_PROBE ; 
 int VDEV_LABELS ; 
 int /*<<< orphan*/  VDEV_PAD_SIZE ; 
 int /*<<< orphan*/  ZIO_CHECKSUM_OFF ; 
 int ZIO_FLAG_CANFAIL ; 
 int ZIO_FLAG_CONFIG_WRITER ; 
 int ZIO_FLAG_DONT_AGGREGATE ; 
 int ZIO_FLAG_DONT_CACHE ; 
 int ZIO_FLAG_DONT_PROPAGATE ; 
 int ZIO_FLAG_PROBE ; 
 int ZIO_FLAG_TRYHARD ; 
 int /*<<< orphan*/  ZIO_PRIORITY_SYNC_READ ; 
 int /*<<< orphan*/  abd_alloc_for_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_async_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_config_held (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_label_offset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_label_t ; 
 int /*<<< orphan*/  vdev_probe_done ; 
 int /*<<< orphan*/  vl_pad2 ; 
 int /*<<< orphan*/  zio_add_child (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  zio_nowait (TYPE_2__*) ; 
 TYPE_2__* zio_null (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 TYPE_2__* zio_read_phys (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

zio_t *
vdev_probe(vdev_t *vd, zio_t *zio)
{
	spa_t *spa = vd->vdev_spa;
	vdev_probe_stats_t *vps = NULL;
	zio_t *pio;

	ASSERT(vd->vdev_ops->vdev_op_leaf);

	/*
	 * Don't probe the probe.
	 */
	if (zio && (zio->io_flags & ZIO_FLAG_PROBE))
		return (NULL);

	/*
	 * To prevent 'probe storms' when a device fails, we create
	 * just one probe i/o at a time.  All zios that want to probe
	 * this vdev will become parents of the probe io.
	 */
	mutex_enter(&vd->vdev_probe_lock);

	if ((pio = vd->vdev_probe_zio) == NULL) {
		vps = kmem_zalloc(sizeof (*vps), KM_SLEEP);

		vps->vps_flags = ZIO_FLAG_CANFAIL | ZIO_FLAG_PROBE |
		    ZIO_FLAG_DONT_CACHE | ZIO_FLAG_DONT_AGGREGATE |
		    ZIO_FLAG_TRYHARD;

		if (spa_config_held(spa, SCL_ZIO, RW_WRITER)) {
			/*
			 * vdev_cant_read and vdev_cant_write can only
			 * transition from TRUE to FALSE when we have the
			 * SCL_ZIO lock as writer; otherwise they can only
			 * transition from FALSE to TRUE.  This ensures that
			 * any zio looking at these values can assume that
			 * failures persist for the life of the I/O.  That's
			 * important because when a device has intermittent
			 * connectivity problems, we want to ensure that
			 * they're ascribed to the device (ENXIO) and not
			 * the zio (EIO).
			 *
			 * Since we hold SCL_ZIO as writer here, clear both
			 * values so the probe can reevaluate from first
			 * principles.
			 */
			vps->vps_flags |= ZIO_FLAG_CONFIG_WRITER;
			vd->vdev_cant_read = B_FALSE;
			vd->vdev_cant_write = B_FALSE;
		}

		vd->vdev_probe_zio = pio = zio_null(NULL, spa, vd,
		    vdev_probe_done, vps,
		    vps->vps_flags | ZIO_FLAG_DONT_PROPAGATE);

		/*
		 * We can't change the vdev state in this context, so we
		 * kick off an async task to do it on our behalf.
		 */
		if (zio != NULL) {
			vd->vdev_probe_wanted = B_TRUE;
			spa_async_request(spa, SPA_ASYNC_PROBE);
		}
	}

	if (zio != NULL)
		zio_add_child(zio, pio);

	mutex_exit(&vd->vdev_probe_lock);

	if (vps == NULL) {
		ASSERT(zio != NULL);
		return (NULL);
	}

	for (int l = 1; l < VDEV_LABELS; l++) {
		zio_nowait(zio_read_phys(pio, vd,
		    vdev_label_offset(vd->vdev_psize, l,
		    offsetof(vdev_label_t, vl_pad2)), VDEV_PAD_SIZE,
		    abd_alloc_for_io(VDEV_PAD_SIZE, B_TRUE),
		    ZIO_CHECKSUM_OFF, vdev_probe_done, vps,
		    ZIO_PRIORITY_SYNC_READ, vps->vps_flags, B_TRUE));
	}

	if (zio == NULL)
		return (pio);

	zio_nowait(pio);
	return (NULL);
}