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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  gcry_mpi_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  det_randomize (int*,size_t,void const*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ gcry_mpi_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  gcry_mpi_mulm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  mpi_import (int*,size_t) ; 

__attribute__((used)) static gcry_mpi_t gensquare(const gcry_mpi_t n, const void *seed, size_t seedlen, uint32_t idx, unsigned secpar) {
        size_t buflen = secpar / 8;
        uint8_t buf[buflen];
        gcry_mpi_t x;

        det_randomize(buf, buflen, seed, seedlen, idx);
        buf[0] &= 0x7f; /* clear upper bit, so that we have x < n */
        x = mpi_import(buf, buflen);
        assert(gcry_mpi_cmp(x, n) < 0);
        gcry_mpi_mulm(x, x, x, n);
        return x;
}