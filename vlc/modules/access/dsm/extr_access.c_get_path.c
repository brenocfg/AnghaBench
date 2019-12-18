#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ stream_t ;
struct TYPE_6__ {int /*<<< orphan*/ * psz_path; } ;
struct TYPE_8__ {char* psz_fullpath; char* psz_share; char* psz_path; TYPE_1__ url; } ;
typedef  TYPE_3__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  backslash_path (char*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 char* vlc_uri_decode_duplicate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool get_path( stream_t *p_access )
{
    access_sys_t *p_sys = p_access->p_sys;
    char *iter;

    if( p_sys->url.psz_path == NULL )
        return false;

    p_sys->psz_fullpath = vlc_uri_decode_duplicate( p_sys->url.psz_path );
    if( p_sys->psz_fullpath == NULL )
        return false;

    backslash_path( p_sys->psz_fullpath );

    /* Is path longer than just "/" ? */
    if( strlen( p_sys->psz_fullpath ) > 1 )
    {
        iter = p_sys->psz_fullpath;
        while( *iter == '\\' ) iter++; /* Handle smb://Host/////Share/ */

        p_sys->psz_share = iter;
    }
    else
    {
        msg_Dbg( p_access, "no share, nor file path provided, will switch to browser");
        return false;
    }

    iter = strchr( p_sys->psz_share, '\\' );
    if( iter == NULL || strlen(iter + 1) == 0 )
    {
        if( iter != NULL ) /* Remove the trailing \ */
            *iter = '\0';
        p_sys->psz_path = "";

        msg_Dbg( p_access, "no file path provided, will switch to browser ");
        return true;
    }

    p_sys->psz_path = iter + 1; /* Skip the first \ */
    *iter = '\0';

    return true;
}