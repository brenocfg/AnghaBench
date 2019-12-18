#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_9__ {int b_wants_substreams; int /*<<< orphan*/  lock; void* psz_sout; int /*<<< orphan*/ * p_stream; scalar_t__ i_out_pace_nocontrol; } ;
typedef  TYPE_1__ sout_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREENULL (void*) ; 
 int /*<<< orphan*/  SOUT_STREAM_WANTS_SUBSTREAMS ; 
 int VLC_VAR_DOINHERIT ; 
 int VLC_VAR_INTEGER ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/ * sout_StreamChainNew (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sout_StreamControl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 char* sout_stream_url_to_chain (int /*<<< orphan*/ ,char const*) ; 
 void* strdup (char const*) ; 
 int /*<<< orphan*/  var_Create (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  var_InheritBool (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* vlc_custom_create (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_1__*) ; 

sout_instance_t *sout_NewInstance( vlc_object_t *p_parent, const char *psz_dest )
{
    sout_instance_t *p_sout;
    char *psz_chain;

    assert( psz_dest != NULL );

    if( psz_dest[0] == '#' )
    {
        psz_chain = strdup( &psz_dest[1] );
    }
    else
    {
        psz_chain = sout_stream_url_to_chain(
            var_InheritBool(p_parent, "sout-display"), psz_dest );
    }
    if(!psz_chain)
        return NULL;

    /* *** Allocate descriptor *** */
    p_sout = vlc_custom_create( p_parent, sizeof( *p_sout ), "stream output" );
    if( p_sout == NULL )
    {
        free( psz_chain );
        return NULL;
    }

    msg_Dbg( p_sout, "using sout chain=`%s'", psz_chain );

    /* *** init descriptor *** */
    p_sout->psz_sout    = strdup( psz_dest );
    p_sout->i_out_pace_nocontrol = 0;
    p_sout->b_wants_substreams = false;

    vlc_mutex_init( &p_sout->lock );
    p_sout->p_stream = NULL;

    var_Create( p_sout, "sout-mux-caching", VLC_VAR_INTEGER | VLC_VAR_DOINHERIT );

    p_sout->p_stream = sout_StreamChainNew( p_sout, psz_chain, NULL, NULL );
    if( p_sout->p_stream )
    {
        free( psz_chain );
        sout_StreamControl( p_sout->p_stream,
                            SOUT_STREAM_WANTS_SUBSTREAMS,
                            &p_sout->b_wants_substreams );
        return p_sout;
    }

    msg_Err( p_sout, "stream chain failed for `%s'", psz_chain );
    free( psz_chain );

    FREENULL( p_sout->psz_sout );

    vlc_mutex_destroy( &p_sout->lock );
    vlc_object_delete(p_sout);
    return NULL;
}