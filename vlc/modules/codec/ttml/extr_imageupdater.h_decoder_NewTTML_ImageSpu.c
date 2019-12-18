#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * p_regions; int /*<<< orphan*/ ** pp_append; } ;
typedef  TYPE_1__ ttml_image_updater_sys_t ;
struct TYPE_7__ {TYPE_1__* p_sys; int /*<<< orphan*/  pf_destroy; int /*<<< orphan*/  pf_update; int /*<<< orphan*/  pf_validate; } ;
typedef  TYPE_2__ subpicture_updater_t ;
typedef  int /*<<< orphan*/  subpicture_t ;
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  TTML_ImageSpuDestroy ; 
 int /*<<< orphan*/  TTML_ImageSpuUpdate ; 
 int /*<<< orphan*/  TTML_ImageSpuValidate ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/ * decoder_NewSubpicture (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static inline subpicture_t *decoder_NewTTML_ImageSpu(decoder_t *p_dec)
{
    ttml_image_updater_sys_t *p_sys = calloc(1, sizeof(*p_sys));
    if(!p_sys)
        return NULL;
    subpicture_updater_t updater = {
        .pf_validate = TTML_ImageSpuValidate,
        .pf_update   = TTML_ImageSpuUpdate,
        .pf_destroy  = TTML_ImageSpuDestroy,
        .p_sys       = p_sys,
    };
    p_sys->p_regions = NULL;
    p_sys->pp_append = &p_sys->p_regions;
    subpicture_t *p_spu = decoder_NewSubpicture(p_dec, &updater);
    if (!p_spu)
        free(p_sys);
    return p_spu;
}