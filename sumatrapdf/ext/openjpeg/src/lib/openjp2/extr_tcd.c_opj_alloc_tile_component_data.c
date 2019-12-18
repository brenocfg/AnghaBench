#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int data; scalar_t__ data_size_needed; scalar_t__ data_size; scalar_t__ ownsData; } ;
typedef  TYPE_1__ opj_tcd_tilecomp_t ;
typedef  int /*<<< orphan*/  OPJ_INT32 ;
typedef  scalar_t__ OPJ_BOOL ;

/* Variables and functions */
 scalar_t__ OPJ_FALSE ; 
 scalar_t__ OPJ_TRUE ; 
 scalar_t__ opj_image_data_alloc (scalar_t__) ; 
 int /*<<< orphan*/  opj_image_data_free (int) ; 

OPJ_BOOL opj_alloc_tile_component_data(opj_tcd_tilecomp_t *l_tilec)
{
    if ((l_tilec->data == 00) ||
            ((l_tilec->data_size_needed > l_tilec->data_size) &&
             (l_tilec->ownsData == OPJ_FALSE))) {
        l_tilec->data = (OPJ_INT32 *) opj_image_data_alloc(l_tilec->data_size_needed);
        if (!l_tilec->data && l_tilec->data_size_needed != 0) {
            return OPJ_FALSE;
        }
        /*fprintf(stderr, "tAllocate data of tilec (int): %d x OPJ_UINT32n",l_data_size);*/
        l_tilec->data_size = l_tilec->data_size_needed;
        l_tilec->ownsData = OPJ_TRUE;
    } else if (l_tilec->data_size_needed > l_tilec->data_size) {
        /* We don't need to keep old data */
        opj_image_data_free(l_tilec->data);
        l_tilec->data = (OPJ_INT32 *) opj_image_data_alloc(l_tilec->data_size_needed);
        if (! l_tilec->data) {
            l_tilec->data_size = 0;
            l_tilec->data_size_needed = 0;
            l_tilec->ownsData = OPJ_FALSE;
            return OPJ_FALSE;
        }
        /*fprintf(stderr, "tReallocate data of tilec (int): from %d to %d x OPJ_UINT32n", l_tilec->data_size, l_data_size);*/
        l_tilec->data_size = l_tilec->data_size_needed;
        l_tilec->ownsData = OPJ_TRUE;
    }
    return OPJ_TRUE;
}