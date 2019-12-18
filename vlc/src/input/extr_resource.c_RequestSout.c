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
typedef  char const sout_instance_t ;
typedef  char const input_resource_t ;

/* Variables and functions */
 int /*<<< orphan*/  DestroySout (char const*) ; 
 int /*<<< orphan*/  VLC_UNUSED (char const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  msg_Dbg (char*,char*) ; 
 char* sout_NewInstance (char*,char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static sout_instance_t *RequestSout( input_resource_t *p_resource,
                                     sout_instance_t *p_sout, const char *psz_sout )
{
#ifdef ENABLE_SOUT
    if( !p_sout && !psz_sout )
    {
        if( p_resource->p_sout )
        {
            msg_Dbg( p_resource->p_sout, "destroying useless sout" );
            DestroySout( p_resource );
        }
        return NULL;
    }

    assert( !p_sout || ( !p_resource->p_sout && !psz_sout ) );

    /* Check the validity of the sout */
    if( p_resource->p_sout &&
        strcmp( p_resource->p_sout->psz_sout, psz_sout ) )
    {
        msg_Dbg( p_resource->p_parent, "destroying unusable sout" );
        DestroySout( p_resource );
    }

    if( psz_sout )
    {
        if( p_resource->p_sout )
        {
            /* Reuse it */
            msg_Dbg( p_resource->p_parent, "reusing sout" );
            msg_Dbg( p_resource->p_parent, "you probably want to use gather stream_out" );
        }
        else
        {
            /* Create a new one */
            p_resource->p_sout = sout_NewInstance( p_resource->p_parent, psz_sout );
        }

        p_sout = p_resource->p_sout;
        p_resource->p_sout = NULL;

        return p_sout;
    }
    else
    {
        p_resource->p_sout = p_sout;
        return NULL;
    }
#else
    VLC_UNUSED (p_resource); VLC_UNUSED (p_sout); VLC_UNUSED (psz_sout);
    return NULL;
#endif
}