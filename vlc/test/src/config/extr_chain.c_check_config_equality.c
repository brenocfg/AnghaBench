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
struct TYPE_4__ {struct TYPE_4__* p_next; int /*<<< orphan*/  psz_value; int /*<<< orphan*/  psz_name; } ;
typedef  TYPE_1__ config_chain_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_config_equality( config_chain_t *p_cfg1, config_chain_t *p_cfg2 )
{
    while(p_cfg1 && p_cfg2)
    {
        assert( !strcmp( p_cfg1->psz_name,  p_cfg2->psz_name ) &&
                !strcmp( p_cfg1->psz_value, p_cfg2->psz_value ) );

        p_cfg1 = p_cfg1->p_next;
        p_cfg2 = p_cfg2->p_next;
    }
    assert(!p_cfg1 && !p_cfg2);
}