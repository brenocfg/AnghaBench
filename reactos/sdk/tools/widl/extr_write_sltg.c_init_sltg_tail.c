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
struct sltg_tail {int funcs_off; int vars_off; int impls_off; int funcs_bytes; int vars_bytes; int impls_bytes; int tdescalias_vt; int res16; int cbAlignment; int res24; int res26; int res2a; int res2c; int res2e; int res30; scalar_t__ type_bytes; scalar_t__ res32; scalar_t__ cbSizeVft; scalar_t__ cbSizeInstance; scalar_t__ res1e; scalar_t__ simple_alias; scalar_t__ res1a; scalar_t__ res18; scalar_t__ res06; scalar_t__ cImplTypes; scalar_t__ cVars; scalar_t__ cFuncs; } ;

/* Variables and functions */

__attribute__((used)) static void init_sltg_tail(struct sltg_tail *tail)
{
    tail->cFuncs = 0;
    tail->cVars = 0;
    tail->cImplTypes = 0;
    tail->res06 = 0;
    tail->funcs_off = -1;
    tail->vars_off = -1;
    tail->impls_off = -1;
    tail->funcs_bytes = -1;
    tail->vars_bytes = -1;
    tail->impls_bytes = -1;
    tail->tdescalias_vt = -1;
    tail->res16 = -1;
    tail->res18 = 0;
    tail->res1a = 0;
    tail->simple_alias = 0;
    tail->res1e = 0;
    tail->cbSizeInstance = 0;
    tail->cbAlignment = 4;
    tail->res24 = -1;
    tail->res26 = -1;
    tail->cbSizeVft = 0;
    tail->res2a = -1;
    tail->res2c = -1;
    tail->res2e = -1;
    tail->res30 = -1;
    tail->res32 = 0;
    tail->type_bytes = 0;
}