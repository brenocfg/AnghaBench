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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  gcry_mpi_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRT_compose (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRT_decompose (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RND_GEN_X ; 
 int /*<<< orphan*/  gcry_mpi_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_mpi_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_mpi_powm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_mpi_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gensquare (int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  initialize_libgcrypt (int) ; 
 int /*<<< orphan*/  mpi_export (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpi_import (void const*,int) ; 
 int read_secpar (void const*) ; 
 int /*<<< orphan*/  store_secpar (void*,int) ; 
 int /*<<< orphan*/  twopowmodphi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uint64_export (void*,int,int /*<<< orphan*/ ) ; 

void FSPRG_Seek(void *state, uint64_t epoch, const void *msk, const void *seed, size_t seedlen) {
        gcry_mpi_t p, q, n, x, xp, xq, kp, kq, xm;
        uint16_t secpar;

        initialize_libgcrypt(false);

        secpar = read_secpar(msk + 0);
        p  = mpi_import(msk + 2 + 0 * (secpar / 2) / 8, (secpar / 2) / 8);
        q  = mpi_import(msk + 2 + 1 * (secpar / 2) / 8, (secpar / 2) / 8);

        n = gcry_mpi_new(0);
        gcry_mpi_mul(n, p, q);

        x = gensquare(n, seed, seedlen, RND_GEN_X, secpar);
        CRT_decompose(&xp, &xq, x, p, q); /* split (mod n) into (mod p) and (mod q) using CRT */

        kp = twopowmodphi(epoch, p); /* compute 2^epoch (mod phi(p)) */
        kq = twopowmodphi(epoch, q); /* compute 2^epoch (mod phi(q)) */

        gcry_mpi_powm(xp, xp, kp, p); /* compute x^(2^epoch) (mod p) */
        gcry_mpi_powm(xq, xq, kq, q); /* compute x^(2^epoch) (mod q) */

        CRT_compose(&xm, xp, xq, p, q); /* combine (mod p) and (mod q) to (mod n) using CRT */

        store_secpar(state + 0, secpar);
        mpi_export(state + 2 + 0 * secpar / 8, secpar / 8, n);
        mpi_export(state + 2 + 1 * secpar / 8, secpar / 8, xm);
        uint64_export(state + 2 + 2 * secpar / 8, 8, epoch);

        gcry_mpi_release(p);
        gcry_mpi_release(q);
        gcry_mpi_release(n);
        gcry_mpi_release(x);
        gcry_mpi_release(xp);
        gcry_mpi_release(xq);
        gcry_mpi_release(kp);
        gcry_mpi_release(kq);
        gcry_mpi_release(xm);
}