#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  sout_access_out_t ;
struct TYPE_9__ {int /*<<< orphan*/  force; } ;
struct TYPE_10__ {int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_demux; void* p_sys; TYPE_1__ obj; } ;
typedef  TYPE_2__ demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  Demux ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_VAR_BOOL ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/ * sout_AccessOutNew (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  var_Create (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ var_InheritBool (TYPE_2__*,char*) ; 
 char* var_InheritString (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  var_SetBool (TYPE_2__*,char*,int) ; 

__attribute__((used)) static int Open( vlc_object_t * p_this )
{
    demux_t *p_demux = (demux_t*)p_this;

    /* Accept only if forced */
    if( !p_demux->obj.force )
        return VLC_EGENERIC;

    char *access = var_InheritString( p_demux, "demuxdump-access" );
    if( access == NULL )
        return VLC_EGENERIC;

    /* --sout-file-append (defaults to false) */
    var_Create( p_demux, "sout-file-append", VLC_VAR_BOOL );
    if( var_InheritBool( p_demux, "demuxdump-append" ) )
        var_SetBool( p_demux, "sout-file-append", true );
    /* --sout-file-format (always false) */
    var_Create( p_demux, "sout-file-format", VLC_VAR_BOOL );

    char *path = var_InheritString( p_demux, "demuxdump-file" );
    if( path == NULL )
    {
        free( access );
        msg_Err( p_demux, "no dump file name given" );
        return VLC_EGENERIC;
    }

    sout_access_out_t *out = sout_AccessOutNew( p_demux, access, path );
    free( path );
    free( access );
    if( out == NULL )
    {
        msg_Err( p_demux, "cannot create output" );
        return VLC_EGENERIC;
    }

    p_demux->p_sys = (void *)out;
    p_demux->pf_demux = Demux;
    p_demux->pf_control = Control;
    return VLC_SUCCESS;
}