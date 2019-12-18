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
struct TYPE_3__ {int /*<<< orphan*/  p_cfg; struct discovery_sys* p_sys; } ;
typedef  TYPE_1__ vlc_renderer_discovery_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct discovery_sys {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_PREFIX ; 
 int OpenCommon (int /*<<< orphan*/ *,struct discovery_sys*,int) ; 
 int VLC_ENOMEM ; 
 struct discovery_sys* calloc (int,int) ; 
 int /*<<< orphan*/  config_ChainParse (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppsz_options ; 

__attribute__((used)) static int
OpenRD( vlc_object_t *p_obj )
{
    vlc_renderer_discovery_t *p_rd = (vlc_renderer_discovery_t *)p_obj;

    struct discovery_sys *p_sys = calloc( 1, sizeof(struct discovery_sys) );
    if( !p_sys )
        return VLC_ENOMEM;
    p_rd->p_sys = p_sys;

    config_ChainParse( p_rd, CFG_PREFIX, ppsz_options, p_rd->p_cfg );

    return OpenCommon( p_obj, p_sys, true );
}