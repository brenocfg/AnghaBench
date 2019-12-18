#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  filter_t ;
struct TYPE_7__ {TYPE_1__* last; int /*<<< orphan*/  obj; } ;
typedef  TYPE_2__ filter_chain_t ;
typedef  int /*<<< orphan*/  config_chain_t ;
struct TYPE_6__ {int /*<<< orphan*/  filter; } ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 char* config_ChainCreate (char**,int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/  config_ChainDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * filter_chain_AppendFilter (TYPE_2__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filter_chain_DeleteFilter (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*,char*) ; 

int filter_chain_AppendFromString( filter_chain_t *chain, const char *str )
{
    char *buf = NULL;
    int ret = 0;

    while( str != NULL && str[0] != '\0' )
    {
        config_chain_t *cfg;
        char *name;

        char *next = config_ChainCreate( &name, &cfg, str );

        str = next;
        free( buf );
        buf = next;

        filter_t *filter = filter_chain_AppendFilter( chain, name, cfg, NULL );
        if( cfg )
            config_ChainDestroy( cfg );

        if( filter == NULL )
        {
            msg_Err( chain->obj, "Failed to append '%s' to chain", name );
            free( name );
            goto error;
        }

        free( name );
        ret++;
    }

    free( buf );
    return ret;

error:
    while( ret > 0 ) /* Unwind */
    {
        filter_chain_DeleteFilter( chain, &chain->last->filter );
        ret--;
    }
    free( buf );
    return VLC_EGENERIC;
}