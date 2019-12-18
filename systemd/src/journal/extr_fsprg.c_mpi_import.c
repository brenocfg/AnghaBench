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
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ gcry_mpi_cmp_ui (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gcry_mpi_get_nbits (int /*<<< orphan*/ ) ; 
 scalar_t__ gcry_mpi_scan (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static gcry_mpi_t mpi_import(const void *buf, size_t buflen) {
        gcry_mpi_t h;
        unsigned len;

        assert_se(gcry_mpi_scan(&h, GCRYMPI_FMT_USG, buf, buflen, NULL) == 0);
        len = (gcry_mpi_get_nbits(h) + 7) / 8;
        assert(len <= buflen);
        assert(gcry_mpi_cmp_ui(h, 0) >= 0);

        return h;
}