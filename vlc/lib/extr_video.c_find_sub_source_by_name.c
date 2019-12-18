#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vout_thread_t ;
typedef  int /*<<< orphan*/  libvlc_media_player_t ;

/* Variables and functions */
 int /*<<< orphan*/ * GetVout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  libvlc_printerr (char*,char const*) ; 
 char* strstr (char*,char const*) ; 
 char* var_GetString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vout_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool find_sub_source_by_name( libvlc_media_player_t *p_mi, const char *restrict name )
{
    vout_thread_t *vout = GetVout( p_mi, 0 );
    if (!vout)
        return false;

    char *psz_sources = var_GetString( vout, "sub-source" );
    if( !psz_sources )
    {
        libvlc_printerr( "%s not enabled", name );
        vout_Release(vout);
        return false;
    }

    /* Find 'name'  */
    char *p = strstr( psz_sources, name );
    free( psz_sources );
    vout_Release(vout);
    return (p != NULL);
}