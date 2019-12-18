#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  p_fmt; } ;
struct TYPE_12__ {int /*<<< orphan*/  p_evt; } ;
struct TYPE_11__ {int /*<<< orphan*/  p_epg; } ;
struct TYPE_10__ {int /*<<< orphan*/  p_meta; } ;
struct TYPE_14__ {TYPE_4__ es_fmt; TYPE_3__ int_epg_evt; TYPE_2__ int_epg; TYPE_1__ int_meta; } ;
struct TYPE_15__ {int i_query; TYPE_5__ u; } ;
struct TYPE_16__ {TYPE_6__ control; } ;
struct TYPE_17__ {TYPE_7__ u; } ;
typedef  TYPE_8__ ts_cmd_t ;

/* Variables and functions */
#define  ES_OUT_SET_ES_FMT 132 
#define  ES_OUT_SET_GROUP_EPG 131 
#define  ES_OUT_SET_GROUP_EPG_EVENT 130 
#define  ES_OUT_SET_GROUP_META 129 
#define  ES_OUT_SET_META 128 
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_epg_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_epg_event_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_meta_Delete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CmdCleanControl( ts_cmd_t *p_cmd )
{
    switch( p_cmd->u.control.i_query )
    {
    case ES_OUT_SET_GROUP_META:
    case ES_OUT_SET_META:
        if( p_cmd->u.control.u.int_meta.p_meta )
            vlc_meta_Delete( p_cmd->u.control.u.int_meta.p_meta );
        break;
    case ES_OUT_SET_GROUP_EPG:
        if( p_cmd->u.control.u.int_epg.p_epg )
            vlc_epg_Delete( p_cmd->u.control.u.int_epg.p_epg );
        break;
    case ES_OUT_SET_GROUP_EPG_EVENT:
        if( p_cmd->u.control.u.int_epg_evt.p_evt )
            vlc_epg_event_Delete( p_cmd->u.control.u.int_epg_evt.p_evt );
        break;
    case ES_OUT_SET_ES_FMT:
        if( p_cmd->u.control.u.es_fmt.p_fmt )
        {
            es_format_Clean( p_cmd->u.control.u.es_fmt.p_fmt );
            free( p_cmd->u.control.u.es_fmt.p_fmt );
        }
        break;
    }
}