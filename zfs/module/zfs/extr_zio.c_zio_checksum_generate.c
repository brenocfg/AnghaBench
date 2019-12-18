#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int zp_checksum; } ;
struct TYPE_8__ {scalar_t__ io_child_type; int /*<<< orphan*/  io_size; int /*<<< orphan*/  io_abd; TYPE_1__ io_prop; int /*<<< orphan*/ * io_bp; } ;
typedef  TYPE_2__ zio_t ;
typedef  enum zio_checksum { ____Placeholder_zio_checksum } zio_checksum ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BP_GET_CHECKSUM (int /*<<< orphan*/ *) ; 
 scalar_t__ BP_IS_GANG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IO_IS_ALLOCATING (TYPE_2__*) ; 
 int ZIO_CHECKSUM_GANG_HEADER ; 
 int ZIO_CHECKSUM_LABEL ; 
 int ZIO_CHECKSUM_OFF ; 
 scalar_t__ ZIO_CHILD_GANG ; 
 int /*<<< orphan*/  zio_checksum_compute (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zio_t *
zio_checksum_generate(zio_t *zio)
{
	blkptr_t *bp = zio->io_bp;
	enum zio_checksum checksum;

	if (bp == NULL) {
		/*
		 * This is zio_write_phys().
		 * We're either generating a label checksum, or none at all.
		 */
		checksum = zio->io_prop.zp_checksum;

		if (checksum == ZIO_CHECKSUM_OFF)
			return (zio);

		ASSERT(checksum == ZIO_CHECKSUM_LABEL);
	} else {
		if (BP_IS_GANG(bp) && zio->io_child_type == ZIO_CHILD_GANG) {
			ASSERT(!IO_IS_ALLOCATING(zio));
			checksum = ZIO_CHECKSUM_GANG_HEADER;
		} else {
			checksum = BP_GET_CHECKSUM(bp);
		}
	}

	zio_checksum_compute(zio, checksum, zio->io_abd, zio->io_size);

	return (zio);
}