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
typedef  unsigned long long uint64_t ;
typedef  int /*<<< orphan*/  gcry_mpi_t ;

/* Variables and functions */
 int /*<<< orphan*/  gcry_mpi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gcry_mpi_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_mpi_mulm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_mpi_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_mpi_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_mpi_set_ui (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcry_mpi_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_mpi_sub_ui (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int) ; 

__attribute__((used)) static gcry_mpi_t twopowmodphi(uint64_t m, const gcry_mpi_t p) {
        gcry_mpi_t phi, r;
        int n;

        phi = gcry_mpi_new(0);
        gcry_mpi_sub_ui(phi, p, 1);

        /* count number of used bits in m */
        for (n = 0; (1ULL << n) <= m; n++)
                ;

        r = gcry_mpi_new(0);
        gcry_mpi_set_ui(r, 1);
        while (n) { /* square and multiply algorithm for fast exponentiation */
                n--;
                gcry_mpi_mulm(r, r, r, phi);
                if (m & ((uint64_t)1 << n)) {
                        gcry_mpi_add(r, r, r);
                        if (gcry_mpi_cmp(r, phi) >= 0)
                                gcry_mpi_sub(r, r, phi);
                }
        }

        gcry_mpi_release(phi);
        return r;
}