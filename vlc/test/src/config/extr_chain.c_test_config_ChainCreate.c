#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* psz_name; char* psz_value; struct TYPE_7__* p_next; } ;
typedef  TYPE_2__ config_chain_t ;
struct TYPE_8__ {TYPE_1__* config; scalar_t__ psz_next; scalar_t__ psz_module; scalar_t__ psz_string; } ;
struct TYPE_6__ {scalar_t__ psz_value; scalar_t__ psz_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_5__* chain_samples ; 
 char* config_ChainCreate (char**,TYPE_2__**,scalar_t__) ; 
 int /*<<< orphan*/  config_ChainDestroy (TYPE_2__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 

__attribute__((used)) static void test_config_ChainCreate()
{
    for( int i = 0; chain_samples[i].psz_string; i++ )
    {
        config_chain_t *p_cfg;
        char *psz_module;
        char *psz_next = config_ChainCreate( &psz_module, &p_cfg, chain_samples[i].psz_string );

        assert( !strcmp( chain_samples[i].psz_module, psz_module ) );
        assert( (!psz_next && !chain_samples[i].psz_next) || !strcmp( chain_samples[i].psz_next, psz_next ) );

        config_chain_t *p_tmp = p_cfg;
        for( int j = 0; chain_samples[i].config[j].psz_name; j++)
        {
            assert( !strcmp( chain_samples[i].config[j].psz_name,  p_tmp->psz_name ) &&
                    !strcmp( chain_samples[i].config[j].psz_value, p_tmp->psz_value ) );
            p_tmp = p_tmp->p_next;
        }
        assert( !p_tmp );

        config_ChainDestroy( p_cfg );
        free( psz_next );
        free( psz_module );
    }
}