#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ jp2_has_colr; } ;
struct TYPE_8__ {int ignore_pclr_cmap_cdef; TYPE_1__ color; int /*<<< orphan*/  j2k; } ;
typedef  TYPE_2__ opj_jp2_t ;
struct TYPE_9__ {int flags; } ;
typedef  TYPE_3__ opj_dparameters_t ;

/* Variables and functions */
 int OPJ_DPARAMETERS_IGNORE_PCLR_CMAP_CDEF_FLAG ; 
 int /*<<< orphan*/  opj_j2k_setup_decoder (int /*<<< orphan*/ ,TYPE_3__*) ; 

void opj_jp2_setup_decoder(opj_jp2_t *jp2, opj_dparameters_t *parameters)
{
    /* setup the J2K codec */
    opj_j2k_setup_decoder(jp2->j2k, parameters);

    /* further JP2 initializations go here */
    jp2->color.jp2_has_colr = 0;
    jp2->ignore_pclr_cmap_cdef = parameters->flags &
                                 OPJ_DPARAMETERS_IGNORE_PCLR_CMAP_CDEF_FLAG;
}