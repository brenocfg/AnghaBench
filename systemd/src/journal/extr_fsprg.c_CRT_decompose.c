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
 int /*<<< orphan*/  gcry_mpi_mod (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  gcry_mpi_new (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CRT_decompose(gcry_mpi_t *xp, gcry_mpi_t *xq, const gcry_mpi_t x, const gcry_mpi_t p, const gcry_mpi_t q) {
        *xp = gcry_mpi_new(0);
        *xq = gcry_mpi_new(0);
        gcry_mpi_mod(*xp, x, p);
        gcry_mpi_mod(*xq, x, q);
}