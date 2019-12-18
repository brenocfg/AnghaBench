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
 int /*<<< orphan*/  check_config_equality (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* config_ChainCreate (char**,int /*<<< orphan*/ **,scalar_t__) ; 
 int /*<<< orphan*/  config_ChainDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * config_ChainDuplicate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__* ppsz_string ; 

__attribute__((used)) static void test_config_ChainDuplicate()
{
    for( int i = 0; ppsz_string[i]; i++ )
    {
        char *psz_module;
        config_chain_t *p_cfg;
        char *psz_next = config_ChainCreate( &psz_module, &p_cfg, ppsz_string[i] );

        config_chain_t *p_cfg_copy = config_ChainDuplicate( p_cfg );
        check_config_equality(p_cfg, p_cfg_copy);

        config_ChainDestroy( p_cfg_copy );
        config_ChainDestroy( p_cfg );
        free( psz_next );
        free( psz_module );
    }
}