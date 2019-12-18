#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * psz_value; struct TYPE_4__* p_next; int /*<<< orphan*/  psz_name; } ;
typedef  TYPE_1__ config_chain_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ChainGetValue (char const**) ; 
 int /*<<< orphan*/  SKIPSPACE (char const*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memchr (char*,char const,int) ; 
 scalar_t__ strchr (char*,char const) ; 
 size_t strcspn (char const*,char*) ; 
 int /*<<< orphan*/  strndup (char const*,size_t) ; 

const char *config_ChainParseOptions( config_chain_t **pp_cfg, const char *psz_opts )
{
    config_chain_t **pp_next = pp_cfg;
    bool first = true;
    do
    {
        if (!first)
            psz_opts++; /* skip previous delimiter */
        SKIPSPACE( psz_opts );

        first = false;

        /* Look for the end of the name (,={}_space_) */
        size_t len = strcspn( psz_opts, "=,{} \t" );
        if( len == 0 )
            continue; /* ignore empty parameter */

        /* Append the new parameter */
        config_chain_t *p_cfg = malloc( sizeof(*p_cfg) );
        if( !p_cfg )
            break;
        p_cfg->psz_name = strndup( psz_opts, len );
        psz_opts += len;
        p_cfg->psz_value = NULL;
        p_cfg->p_next = NULL;

        *pp_next = p_cfg;
        pp_next = &p_cfg->p_next;

        /* Extract the option value */
        SKIPSPACE( psz_opts );
        if( strchr( "={", *psz_opts ) )
        {
            p_cfg->psz_value = ChainGetValue( &psz_opts );
            SKIPSPACE( psz_opts );
        }
    }
    while( !memchr( "}", *psz_opts, 2 ) );

    if( *psz_opts ) psz_opts++; /* skip '}' */;
    SKIPSPACE( psz_opts );

    return psz_opts;
}