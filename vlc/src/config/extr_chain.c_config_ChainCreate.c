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
typedef  int /*<<< orphan*/  config_chain_t ;

/* Variables and functions */
 int /*<<< orphan*/  SKIPSPACE (char const*) ; 
 char* config_ChainParseOptions (int /*<<< orphan*/ **,char const*) ; 
 size_t strcspn (char const*,char*) ; 
 char* strdup (char const*) ; 
 char* strndup (char const*,size_t) ; 

char *config_ChainCreate( char **ppsz_name, config_chain_t **pp_cfg,
                          const char *psz_chain )
{
    size_t len;

    *ppsz_name = NULL;
    *pp_cfg    = NULL;

    if( !psz_chain )
        return NULL;
    SKIPSPACE( psz_chain );

    /* Look for parameter (a {...} or :...) or end of name (space or nul) */
    len = strcspn( psz_chain, "{: \t" );
    *ppsz_name = strndup( psz_chain, len );
    psz_chain += len;

    /* Parse the parameters */
    SKIPSPACE( psz_chain );
    if( *psz_chain == '{' )
        psz_chain = config_ChainParseOptions( pp_cfg, psz_chain );

    if( *psz_chain == ':' )
        return strdup( psz_chain + 1 );

    return NULL;
}