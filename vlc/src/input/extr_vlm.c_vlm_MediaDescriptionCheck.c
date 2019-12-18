#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int i_media; TYPE_2__** media; } ;
typedef  TYPE_3__ vlm_t ;
struct TYPE_10__ {char* psz_name; scalar_t__ id; } ;
typedef  TYPE_4__ vlm_media_t ;
struct TYPE_7__ {scalar_t__ id; char* psz_name; } ;
struct TYPE_8__ {TYPE_1__ cfg; } ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int vlm_MediaDescriptionCheck( vlm_t *p_vlm, vlm_media_t *p_cfg )
{
    if( !p_cfg || !p_cfg->psz_name ||
        !strcmp( p_cfg->psz_name, "all" ) || !strcmp( p_cfg->psz_name, "media" ) || !strcmp( p_cfg->psz_name, "schedule" ) )
        return VLC_EGENERIC;

    for( int i = 0; i < p_vlm->i_media; i++ )
    {
        if( p_vlm->media[i]->cfg.id == p_cfg->id )
            continue;
        if( !strcmp( p_vlm->media[i]->cfg.psz_name, p_cfg->psz_name ) )
            return VLC_EGENERIC;
    }
    return VLC_SUCCESS;
}