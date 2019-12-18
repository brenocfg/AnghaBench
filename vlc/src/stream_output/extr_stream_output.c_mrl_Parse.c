#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* psz_name; void* psz_way; void* psz_access; } ;
typedef  TYPE_1__ mrl_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 void* strdup (char const*) ; 

__attribute__((used)) static int mrl_Parse( mrl_t *p_mrl, const char *psz_mrl )
{
    char * psz_dup = strdup( psz_mrl );
    char * psz_parser = psz_dup;
    const char * psz_access;
    const char * psz_way;
    char * psz_name;

    /* *** first parse psz_dest */
    while( *psz_parser && *psz_parser != ':' )
    {
        if( *psz_parser == '{' )
        {
            while( *psz_parser && *psz_parser != '}' )
            {
                psz_parser++;
            }
            if( *psz_parser )
            {
                psz_parser++;
            }
        }
        else
        {
            psz_parser++;
        }
    }
#if defined( _WIN32 ) || defined( __OS2__ )
    if( psz_parser - psz_dup == 1 )
    {
        /* msg_Warn( p_sout, "drive letter %c: found in source string",
                          *psz_dup ) ; */
        *psz_parser = '\0';
    }
#endif

    if( !*psz_parser )
    {
        psz_access = psz_way = "";
        psz_name = psz_dup;
    }
    else
    {
        *psz_parser++ = '\0';

        /* let's skip '//' */
        if( psz_parser[0] == '/' && psz_parser[1] == '/' )
        {
            psz_parser += 2 ;
        }

        psz_name = psz_parser ;

        /* Come back to parse the access and mux plug-ins */
        psz_parser = psz_dup;

        if( !*psz_parser )
        {
            /* No access */
            psz_access = "";
        }
        else if( *psz_parser == '/' )
        {
            /* No access */
            psz_access = "";
            psz_parser++;
        }
        else
        {
            psz_access = psz_parser;

            while( *psz_parser && *psz_parser != '/' )
            {
                if( *psz_parser == '{' )
                {
                    while( *psz_parser && *psz_parser != '}' )
                    {
                        psz_parser++;
                    }
                    if( *psz_parser )
                    {
                        psz_parser++;
                    }
                }
                else
                {
                    psz_parser++;
                }
            }

            if( *psz_parser == '/' )
            {
                *psz_parser++ = '\0';
            }
        }

        if( !*psz_parser )
        {
            /* No mux */
            psz_way = "";
        }
        else
        {
            psz_way = psz_parser;
        }
    }

    p_mrl->psz_access = strdup( psz_access );
    p_mrl->psz_way    = strdup( psz_way );
    p_mrl->psz_name   = strdup( psz_name );

    free( psz_dup );
    return( VLC_SUCCESS );
}