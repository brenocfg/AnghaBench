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
typedef  int /*<<< orphan*/  gcry_mpi_t ;

/* Variables and functions */
 int /*<<< orphan*/  GCRYMPI_FMT_USG ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ gcry_mpi_cmp_ui (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int gcry_mpi_get_nbits (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  gcry_mpi_print (int /*<<< orphan*/ ,void*,unsigned int,size_t*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  memzero (void*,size_t) ; 

__attribute__((used)) static void mpi_export(void *buf, size_t buflen, const gcry_mpi_t x) {
        unsigned len;
        size_t nwritten;

        assert(gcry_mpi_cmp_ui(x, 0) >= 0);
        len = (gcry_mpi_get_nbits(x) + 7) / 8;
        assert(len <= buflen);
        memzero(buf, buflen);
        gcry_mpi_print(GCRYMPI_FMT_USG, buf + (buflen - len), len, &nwritten, x);
        assert(nwritten == len);
}