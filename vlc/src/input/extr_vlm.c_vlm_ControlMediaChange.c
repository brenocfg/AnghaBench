#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlm_t ;
struct TYPE_10__ {scalar_t__ b_vod; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ vlm_media_t ;
struct TYPE_12__ {scalar_t__ b_vod; } ;
struct TYPE_11__ {TYPE_3__ cfg; } ;
typedef  TYPE_2__ vlm_media_sys_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 TYPE_2__* vlm_ControlMediaGetById (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vlm_MediaDescriptionCheck (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int vlm_OnMediaUpdate (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  vlm_media_Clean (TYPE_3__*) ; 
 int /*<<< orphan*/  vlm_media_Copy (TYPE_3__*,TYPE_1__*) ; 

__attribute__((used)) static int vlm_ControlMediaChange( vlm_t *p_vlm, vlm_media_t *p_cfg )
{
    vlm_media_sys_t *p_media = vlm_ControlMediaGetById( p_vlm, p_cfg->id );

    /* */
    if( !p_media || vlm_MediaDescriptionCheck( p_vlm, p_cfg ) )
        return VLC_EGENERIC;
    if( ( p_media->cfg.b_vod && !p_cfg->b_vod ) || ( !p_media->cfg.b_vod && p_cfg->b_vod ) )
        return VLC_EGENERIC;

    if( 0 )
    {
        /* TODO check what are the changes being done (stop instance if needed) */
    }

    vlm_media_Clean( &p_media->cfg );
    vlm_media_Copy( &p_media->cfg, p_cfg );

    return vlm_OnMediaUpdate( p_vlm, p_media );
}