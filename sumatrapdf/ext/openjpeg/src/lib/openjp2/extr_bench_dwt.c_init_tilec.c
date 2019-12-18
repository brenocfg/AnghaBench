#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void** data; scalar_t__ numresolutions; void* y1; void* x1; void* y0; void* x0; TYPE_2__* resolutions; } ;
typedef  TYPE_1__ opj_tcd_tilecomp_t ;
struct TYPE_6__ {void* y1; void* x1; void* y0; void* x0; } ;
typedef  TYPE_2__ opj_tcd_resolution_t ;
typedef  scalar_t__ OPJ_UINT32 ;
typedef  void* OPJ_INT32 ;

/* Variables and functions */
 void* getValue (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ opj_calloc (scalar_t__,int) ; 
 void* opj_int_ceildivpow2 (void*,void*) ; 
 scalar_t__ opj_malloc (int) ; 

void init_tilec(opj_tcd_tilecomp_t * l_tilec,
                OPJ_INT32 x0,
                OPJ_INT32 y0,
                OPJ_INT32 x1,
                OPJ_INT32 y1,
                OPJ_UINT32 numresolutions)
{
    opj_tcd_resolution_t* l_res;
    OPJ_UINT32 resno, l_level_no;
    size_t i, nValues;

    memset(l_tilec, 0, sizeof(*l_tilec));
    l_tilec->x0 = x0;
    l_tilec->y0 = y0;
    l_tilec->x1 = x1;
    l_tilec->y1 = y1;
    nValues = (size_t)(l_tilec->x1 - l_tilec->x0) *
              (size_t)(l_tilec->y1 - l_tilec->y0);
    l_tilec->data = (OPJ_INT32*) opj_malloc(sizeof(OPJ_INT32) * nValues);
    for (i = 0; i < nValues; i++) {
        l_tilec->data[i] = getValue((OPJ_UINT32)i);
    }
    l_tilec->numresolutions = numresolutions;
    l_tilec->resolutions = (opj_tcd_resolution_t*) opj_calloc(
                               l_tilec->numresolutions,
                               sizeof(opj_tcd_resolution_t));

    l_level_no = l_tilec->numresolutions;
    l_res = l_tilec->resolutions;

    /* Adapted from opj_tcd_init_tile() */
    for (resno = 0; resno < l_tilec->numresolutions; ++resno) {

        --l_level_no;

        /* border for each resolution level (global) */
        l_res->x0 = opj_int_ceildivpow2(l_tilec->x0, (OPJ_INT32)l_level_no);
        l_res->y0 = opj_int_ceildivpow2(l_tilec->y0, (OPJ_INT32)l_level_no);
        l_res->x1 = opj_int_ceildivpow2(l_tilec->x1, (OPJ_INT32)l_level_no);
        l_res->y1 = opj_int_ceildivpow2(l_tilec->y1, (OPJ_INT32)l_level_no);

        ++l_res;
    }
}