#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_6__ {int bw_txg; scalar_t__ bw_data; int bw_index; } ;
typedef  TYPE_1__ bufwad_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ bcmp (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ztest_random (unsigned long long) ; 

void
compare_and_update_pbbufs(uint64_t s, bufwad_t *packbuf, bufwad_t *bigbuf,
    uint64_t bigsize, uint64_t n, uint64_t chunksize, uint64_t txg)
{
	uint64_t i;
	bufwad_t *pack;
	bufwad_t *bigH;
	bufwad_t *bigT;

	/*
	 * For each index from n to n + s, verify that the existing bufwad
	 * in packobj matches the bufwads at the head and tail of the
	 * corresponding chunk in bigobj.  Then update all three bufwads
	 * with the new values we want to write out.
	 */
	for (i = 0; i < s; i++) {
		/* LINTED */
		pack = (bufwad_t *)((char *)packbuf + i * sizeof (bufwad_t));
		/* LINTED */
		bigH = (bufwad_t *)((char *)bigbuf + i * chunksize);
		/* LINTED */
		bigT = (bufwad_t *)((char *)bigH + chunksize) - 1;

		ASSERT((uintptr_t)bigH - (uintptr_t)bigbuf < bigsize);
		ASSERT((uintptr_t)bigT - (uintptr_t)bigbuf < bigsize);

		if (pack->bw_txg > txg)
			fatal(0, "future leak: got %llx, open txg is %llx",
			    pack->bw_txg, txg);

		if (pack->bw_data != 0 && pack->bw_index != n + i)
			fatal(0, "wrong index: got %llx, wanted %llx+%llx",
			    pack->bw_index, n, i);

		if (bcmp(pack, bigH, sizeof (bufwad_t)) != 0)
			fatal(0, "pack/bigH mismatch in %p/%p", pack, bigH);

		if (bcmp(pack, bigT, sizeof (bufwad_t)) != 0)
			fatal(0, "pack/bigT mismatch in %p/%p", pack, bigT);

		pack->bw_index = n + i;
		pack->bw_txg = txg;
		pack->bw_data = 1 + ztest_random(-2ULL);

		*bigH = *pack;
		*bigT = *pack;
	}
}