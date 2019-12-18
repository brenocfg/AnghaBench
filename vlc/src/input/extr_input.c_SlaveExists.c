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
struct TYPE_3__ {int /*<<< orphan*/  psz_uri; } ;
typedef  TYPE_1__ input_item_slave_t ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool SlaveExists( input_item_slave_t **pp_slaves, int i_slaves,
                         const char *psz_uri)
{
    for( int i = 0; i < i_slaves; i++ )
    {
        if( pp_slaves[i] != NULL
         && !strcmp( pp_slaves[i]->psz_uri, psz_uri ) )
            return true;
    }
    return false;
}