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
 int /*<<< orphan*/  gcry_mpi_add_ui (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ gcry_prime_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpi_import (int*,size_t) ; 

__attribute__((used)) static gcry_mpi_t genprime3mod4(int bits, const void *seed, size_t seedlen, uint32_t idx) {
        size_t buflen = bits / 8;
        uint8_t buf[buflen];
        gcry_mpi_t p;

        assert(bits % 8 == 0);
        assert(buflen > 0);

        det_randomize(buf, buflen, seed, seedlen, idx);
        buf[0] |= 0xc0; /* set upper two bits, so that n=pq has maximum size */
        buf[buflen - 1] |= 0x03; /* set lower two bits, to have result 3 (mod 4) */

        p = mpi_import(buf, buflen);
        while (gcry_prime_check(p, 0))
                gcry_mpi_add_ui(p, p, 4);

        return p;
}