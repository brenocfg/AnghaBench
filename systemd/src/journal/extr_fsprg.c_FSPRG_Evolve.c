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
 int /*<<< orphan*/  gcry_mpi_mulm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_mpi_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initialize_libgcrypt (int) ; 
 int /*<<< orphan*/  mpi_export (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpi_import (void*,int) ; 
 int read_secpar (void*) ; 
 int /*<<< orphan*/  uint64_export (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uint64_import (void*,int) ; 

void FSPRG_Evolve(void *state) {
        gcry_mpi_t n, x;
        uint16_t secpar;
        uint64_t epoch;

        initialize_libgcrypt(false);

        secpar = read_secpar(state + 0);
        n = mpi_import(state + 2 + 0 * secpar / 8, secpar / 8);
        x = mpi_import(state + 2 + 1 * secpar / 8, secpar / 8);
        epoch = uint64_import(state + 2 + 2 * secpar / 8, 8);

        gcry_mpi_mulm(x, x, x, n);
        epoch++;

        mpi_export(state + 2 + 1 * secpar / 8, secpar / 8, x);
        uint64_export(state + 2 + 2 * secpar / 8, 8, epoch);

        gcry_mpi_release(n);
        gcry_mpi_release(x);
}