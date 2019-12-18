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
typedef  int /*<<< orphan*/  zio_t ;
typedef  int /*<<< orphan*/  zio_priority_t ;
typedef  int /*<<< orphan*/  zio_done_func_t ;
typedef  int /*<<< orphan*/  zbookmark_phys_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  enum zio_flag { ____Placeholder_zio_flag } zio_flag ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int ZIO_FLAG_IO_REWRITE ; 
 int /*<<< orphan*/  ZIO_REWRITE_PIPELINE ; 
 int /*<<< orphan*/  ZIO_STAGE_OPEN ; 
 int /*<<< orphan*/  ZIO_TYPE_WRITE ; 
 int /*<<< orphan*/ * zio_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

zio_t *
zio_rewrite(zio_t *pio, spa_t *spa, uint64_t txg, blkptr_t *bp, abd_t *data,
    uint64_t size, zio_done_func_t *done, void *private,
    zio_priority_t priority, enum zio_flag flags, zbookmark_phys_t *zb)
{
	zio_t *zio;

	zio = zio_create(pio, spa, txg, bp, data, size, size, done, private,
	    ZIO_TYPE_WRITE, priority, flags | ZIO_FLAG_IO_REWRITE, NULL, 0, zb,
	    ZIO_STAGE_OPEN, ZIO_REWRITE_PIPELINE);

	return (zio);
}