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
struct TYPE_6__ {double margin_ratio; int /*<<< orphan*/  p_default_style; int /*<<< orphan*/  region; } ;
typedef  TYPE_1__ subtext_updater_sys_t ;
struct TYPE_7__ {TYPE_1__* p_sys; int /*<<< orphan*/  pf_destroy; int /*<<< orphan*/  pf_update; int /*<<< orphan*/  pf_validate; } ;
typedef  TYPE_2__ subpicture_updater_t ;
typedef  int /*<<< orphan*/  subpicture_t ;
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  STYLE_NO_DEFAULTS ; 
 int /*<<< orphan*/  SubpictureTextDestroy ; 
 int /*<<< orphan*/  SubpictureTextUpdate ; 
 int /*<<< orphan*/  SubpictureTextValidate ; 
 int /*<<< orphan*/  SubpictureUpdaterSysRegionInit (int /*<<< orphan*/ *) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/ * decoder_NewSubpicture (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  text_style_Create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  text_style_Delete (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline subpicture_t *decoder_NewSubpictureText(decoder_t *decoder)
{
    subtext_updater_sys_t *sys = calloc(1, sizeof(*sys));
    subpicture_updater_t updater = {
        .pf_validate = SubpictureTextValidate,
        .pf_update   = SubpictureTextUpdate,
        .pf_destroy  = SubpictureTextDestroy,
        .p_sys       = sys,
    };
    SubpictureUpdaterSysRegionInit( &sys->region );
    sys->margin_ratio = 0.04;
    sys->p_default_style = text_style_Create( STYLE_NO_DEFAULTS );
    if(unlikely(!sys->p_default_style))
    {
        free(sys);
        return NULL;
    }
    subpicture_t *subpic = decoder_NewSubpicture(decoder, &updater);
    if (!subpic)
    {
        text_style_Delete(sys->p_default_style);
        free(sys);
    }
    return subpic;
}