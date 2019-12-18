#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_readdir; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_5__ {int /*<<< orphan*/ * psz_share; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  BrowseDirectory ; 
 int /*<<< orphan*/  BrowseShare ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  access_vaDirectoryControlHelper ; 

__attribute__((used)) static int BrowserInit( stream_t *p_access )
{
    access_sys_t *p_sys = p_access->p_sys;

    if( p_sys->psz_share == NULL )
        p_access->pf_readdir = BrowseShare;
    else
        p_access->pf_readdir = BrowseDirectory;
    p_access->pf_control = access_vaDirectoryControlHelper;

    return VLC_SUCCESS;
}