#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {char* psz_access; char* psz_path; int /*<<< orphan*/ * p_module; int /*<<< orphan*/ * pf_control; int /*<<< orphan*/ * pf_write; int /*<<< orphan*/ * pf_read; int /*<<< orphan*/ * pf_seek; int /*<<< orphan*/ * p_sys; int /*<<< orphan*/  p_cfg; } ;
typedef  TYPE_1__ sout_access_out_t ;

/* Variables and functions */
 char* config_ChainCreate (char**,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * module_need (TYPE_1__*,char*,char*,int) ; 
 char* strdup (char const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 TYPE_1__* vlc_custom_create (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_1__*) ; 

sout_access_out_t *sout_AccessOutNew( vlc_object_t *p_sout,
                                      const char *psz_access, const char *psz_name )
{
    sout_access_out_t *p_access;
    char              *psz_next;

    p_access = vlc_custom_create( p_sout, sizeof( *p_access ), "access out" );
    if( !p_access )
        return NULL;

    psz_next = config_ChainCreate( &p_access->psz_access, &p_access->p_cfg,
                                   psz_access );
    free( psz_next );
    p_access->psz_path   = strdup( psz_name ? psz_name : "" );
    if( unlikely(p_access->psz_path == NULL) )
        goto error;
    p_access->p_sys      = NULL;
    p_access->pf_seek    = NULL;
    p_access->pf_read    = NULL;
    p_access->pf_write   = NULL;
    p_access->pf_control = NULL;
    p_access->p_module   = NULL;

    p_access->p_module   =
        module_need( p_access, "sout access", p_access->psz_access, true );

    if( !p_access->p_module )
    {
        free( p_access->psz_path );
error:
        free( p_access->psz_access );
        vlc_object_delete(p_access);
        return( NULL );
    }

    return p_access;
}