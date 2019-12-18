#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_max; int /*<<< orphan*/  i_min; } ;
struct TYPE_10__ {int /*<<< orphan*/  scanlist_format; int /*<<< orphan*/ * psz_scanlist_file; TYPE_1__ frequency; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ scan_parameter_t ;
struct TYPE_9__ {int /*<<< orphan*/  frequency_max; int /*<<< orphan*/  frequency_min; } ;
struct TYPE_11__ {TYPE_2__ info; } ;
typedef  TYPE_4__ frontend_t ;
struct TYPE_12__ {TYPE_4__* p_frontend; } ;
typedef  TYPE_5__ dvb_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  FORMAT_DVBv3 ; 
 int /*<<< orphan*/  SCAN_DVB_S ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_SYSDATA_DIR ; 
 int asprintf (int /*<<< orphan*/ **,char*,char*,char*) ; 
 char* config_GetSysPath (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* var_InheritString (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int ScanParametersDvbS( vlc_object_t *p_access, dvb_sys_t *p_sys, scan_parameter_t *p_scan )
{
    const frontend_t *p_frontend = p_sys->p_frontend;

    p_scan->type = SCAN_DVB_S;

    p_scan->frequency.i_min = p_frontend->info.frequency_min;
    p_scan->frequency.i_max = p_frontend->info.frequency_max;
    /* set satellite config file path */
    char *psz_name = var_InheritString( p_access, "dvb-satellite" );
    if( psz_name )
    {
        char *data_dir = config_GetSysPath(VLC_SYSDATA_DIR, "dvb/dvb-s");
        if( !data_dir || -1 ==  asprintf( &p_scan->psz_scanlist_file,
            "%s/%s", data_dir, psz_name ) )
        {
            p_scan->psz_scanlist_file = NULL;
        }
        p_scan->scanlist_format = FORMAT_DVBv3;
        free( data_dir );
        free( psz_name );
    }

    return VLC_SUCCESS;
}