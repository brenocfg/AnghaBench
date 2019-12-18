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
struct TYPE_3__ {int uio_loffset; int /*<<< orphan*/  uio_skip; int /*<<< orphan*/  uio_resid; int /*<<< orphan*/  uio_limit; int /*<<< orphan*/  uio_segflg; scalar_t__ uio_iovcnt; int /*<<< orphan*/ * uio_bvec; } ;
typedef  TYPE_1__ uio_t ;
struct bio {scalar_t__ bi_vcnt; int /*<<< orphan*/ * bi_io_vec; } ;

/* Variables and functions */
 size_t BIO_BI_IDX (struct bio*) ; 
 int BIO_BI_SECTOR (struct bio*) ; 
 int /*<<< orphan*/  BIO_BI_SIZE (struct bio*) ; 
 int /*<<< orphan*/  BIO_BI_SKIP (struct bio*) ; 
 int /*<<< orphan*/  MAXOFFSET_T ; 
 int /*<<< orphan*/  UIO_BVEC ; 

__attribute__((used)) static void
uio_from_bio(uio_t *uio, struct bio *bio)
{
	uio->uio_bvec = &bio->bi_io_vec[BIO_BI_IDX(bio)];
	uio->uio_iovcnt = bio->bi_vcnt - BIO_BI_IDX(bio);
	uio->uio_loffset = BIO_BI_SECTOR(bio) << 9;
	uio->uio_segflg = UIO_BVEC;
	uio->uio_limit = MAXOFFSET_T;
	uio->uio_resid = BIO_BI_SIZE(bio);
	uio->uio_skip = BIO_BI_SKIP(bio);
}