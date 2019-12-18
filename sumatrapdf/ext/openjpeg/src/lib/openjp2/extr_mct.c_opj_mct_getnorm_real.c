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
typedef  size_t OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_FLOAT64 ;

/* Variables and functions */
 int /*<<< orphan*/ * opj_mct_norms_real ; 

OPJ_FLOAT64 opj_mct_getnorm_real(OPJ_UINT32 compno)
{
    return opj_mct_norms_real[compno];
}