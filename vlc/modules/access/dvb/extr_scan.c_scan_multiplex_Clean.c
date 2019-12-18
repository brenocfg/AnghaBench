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
struct TYPE_3__ {size_t i_services; int /*<<< orphan*/ * psz_network_name; int /*<<< orphan*/ * pp_services; } ;
typedef  TYPE_1__ scan_multiplex_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scan_service_Delete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scan_multiplex_Clean( scan_multiplex_t *p_mplex )
{
    for( size_t i=0; i<p_mplex->i_services; i++ )
        scan_service_Delete( p_mplex->pp_services[i] );
    free( p_mplex->pp_services );
    free( p_mplex->psz_network_name );
}