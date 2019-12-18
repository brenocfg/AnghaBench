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
 int /*<<< orphan*/  gcry_mpi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  gcry_mpi_invm (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  gcry_mpi_mul (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_mpi_mulm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  gcry_mpi_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_mpi_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_mpi_subm (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void CRT_compose(gcry_mpi_t *x, const gcry_mpi_t xp, const gcry_mpi_t xq, const gcry_mpi_t p, const gcry_mpi_t q) {
        gcry_mpi_t a, u;

        a = gcry_mpi_new(0);
        u = gcry_mpi_new(0);
        *x = gcry_mpi_new(0);
        gcry_mpi_subm(a, xq, xp, q);
        gcry_mpi_invm(u, p, q);
        gcry_mpi_mulm(a, a, u, q); /* a = (xq - xp) / p  (mod q) */
        gcry_mpi_mul(*x, p, a);
        gcry_mpi_add(*x, *x, xp); /* x = p * ((xq - xp) / p mod q) + xp */
        gcry_mpi_release(a);
        gcry_mpi_release(u);
}