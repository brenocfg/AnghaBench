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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  gcry_mpi_t ;

/* Variables and functions */
 int /*<<< orphan*/  RND_GEN_X ; 
 int /*<<< orphan*/  gcry_mpi_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gensquare (int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  initialize_libgcrypt (int) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int) ; 
 int /*<<< orphan*/  memzero (void*,int) ; 
 int /*<<< orphan*/  mpi_export (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpi_import (void const*,int) ; 
 int read_secpar (void const*) ; 

void FSPRG_GenState0(void *state, const void *mpk, const void *seed, size_t seedlen) {
        gcry_mpi_t n, x;
        uint16_t secpar;

        initialize_libgcrypt(false);

        secpar = read_secpar(mpk + 0);
        n = mpi_import(mpk + 2, secpar / 8);
        x = gensquare(n, seed, seedlen, RND_GEN_X, secpar);

        memcpy(state, mpk, 2 + secpar / 8);
        mpi_export(state + 2 + 1 * secpar / 8, secpar / 8, x);
        memzero(state + 2 + 2 * secpar / 8, 8);

        gcry_mpi_release(n);
        gcry_mpi_release(x);
}