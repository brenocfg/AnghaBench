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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {int /*<<< orphan*/  i_scanlist; scalar_t__ p_scanlist; int /*<<< orphan*/  p_obj; } ;
typedef  TYPE_1__ scan_t ;
struct TYPE_6__ {scalar_t__ type; scalar_t__ scanlist_format; scalar_t__ psz_scanlist_file; } ;
typedef  TYPE_2__ scan_parameter_t ;

/* Variables and functions */
 scalar_t__ FORMAT_DVBv3 ; 
 scalar_t__ FORMAT_DVBv5 ; 
 scalar_t__ SCAN_DVB_S ; 
 scalar_t__ SCAN_DVB_T ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ scan_list_dvbv3_load (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ scan_list_dvbv5_load (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scan_Prepare( vlc_object_t *p_obj, const scan_parameter_t *p_parameter, scan_t *p_scan )
{
    if( p_parameter->type == SCAN_DVB_S &&
        p_parameter->psz_scanlist_file && p_parameter->scanlist_format == FORMAT_DVBv3 )
    {
        p_scan->p_scanlist =
                scan_list_dvbv3_load( p_obj, p_parameter->psz_scanlist_file, &p_scan->i_scanlist );
        if( p_scan->p_scanlist )
            msg_Dbg( p_scan->p_obj, "using satellite config file (%s)", p_parameter->psz_scanlist_file );
    }
    else if( p_parameter->psz_scanlist_file &&
             p_parameter->scanlist_format == FORMAT_DVBv5 )
    {
        if( p_parameter->type == SCAN_DVB_T )
        {
            p_scan->p_scanlist = scan_list_dvbv5_load( p_obj,
                                                       p_parameter->psz_scanlist_file,
                                                       &p_scan->i_scanlist );
        }
    }
}