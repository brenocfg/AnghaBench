#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_15__ {int /*<<< orphan*/  b_byteswap; int /*<<< orphan*/ * b_pabd; } ;
struct TYPE_14__ {int /*<<< orphan*/ * b_rabd; } ;
struct TYPE_16__ {TYPE_2__ b_l1hdr; TYPE_1__ b_crypt_hdr; } ;
typedef  TYPE_3__ arc_buf_hdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCSTAT_BUMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARCSTAT_INCR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DMU_BSWAP_NUMFUNCS ; 
 int /*<<< orphan*/  HDR_GET_LSIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  HDR_GET_PSIZE (TYPE_3__*) ; 
 int HDR_HAS_L1HDR (TYPE_3__*) ; 
 scalar_t__ HDR_HAS_RABD (TYPE_3__*) ; 
 scalar_t__ HDR_L2_WRITING (TYPE_3__*) ; 
 int /*<<< orphan*/  IMPLY (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  arc_free_data_abd (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  arc_hdr_free_on_write (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  arc_hdr_size (TYPE_3__*) ; 
 int /*<<< orphan*/  arcstat_compressed_size ; 
 int /*<<< orphan*/  arcstat_l2_free_on_write ; 
 int /*<<< orphan*/  arcstat_raw_size ; 
 int /*<<< orphan*/  arcstat_uncompressed_size ; 

__attribute__((used)) static void
arc_hdr_free_abd(arc_buf_hdr_t *hdr, boolean_t free_rdata)
{
	uint64_t size = (free_rdata) ? HDR_GET_PSIZE(hdr) : arc_hdr_size(hdr);

	ASSERT(HDR_HAS_L1HDR(hdr));
	ASSERT(hdr->b_l1hdr.b_pabd != NULL || HDR_HAS_RABD(hdr));
	IMPLY(free_rdata, HDR_HAS_RABD(hdr));

	/*
	 * If the hdr is currently being written to the l2arc then
	 * we defer freeing the data by adding it to the l2arc_free_on_write
	 * list. The l2arc will free the data once it's finished
	 * writing it to the l2arc device.
	 */
	if (HDR_L2_WRITING(hdr)) {
		arc_hdr_free_on_write(hdr, free_rdata);
		ARCSTAT_BUMP(arcstat_l2_free_on_write);
	} else if (free_rdata) {
		arc_free_data_abd(hdr, hdr->b_crypt_hdr.b_rabd, size, hdr);
	} else {
		arc_free_data_abd(hdr, hdr->b_l1hdr.b_pabd, size, hdr);
	}

	if (free_rdata) {
		hdr->b_crypt_hdr.b_rabd = NULL;
		ARCSTAT_INCR(arcstat_raw_size, -size);
	} else {
		hdr->b_l1hdr.b_pabd = NULL;
	}

	if (hdr->b_l1hdr.b_pabd == NULL && !HDR_HAS_RABD(hdr))
		hdr->b_l1hdr.b_byteswap = DMU_BSWAP_NUMFUNCS;

	ARCSTAT_INCR(arcstat_compressed_size, -size);
	ARCSTAT_INCR(arcstat_uncompressed_size, -HDR_GET_LSIZE(hdr));
}