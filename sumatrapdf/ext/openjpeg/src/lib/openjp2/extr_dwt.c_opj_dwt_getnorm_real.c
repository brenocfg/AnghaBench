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
typedef  int OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_FLOAT64 ;

/* Variables and functions */
 int /*<<< orphan*/ ** opj_dwt_norms_real ; 

OPJ_FLOAT64 opj_dwt_getnorm_real(OPJ_UINT32 level, OPJ_UINT32 orient)
{
    /* FIXME ! This is just a band-aid to avoid a buffer overflow */
    /* but the array should really be extended up to 33 resolution levels */
    /* See https://github.com/uclouvain/openjpeg/issues/493 */
    if (orient == 0 && level >= 10) {
        level = 9;
    } else if (orient > 0 && level >= 9) {
        level = 8;
    }
    return opj_dwt_norms_real[orient][level];
}