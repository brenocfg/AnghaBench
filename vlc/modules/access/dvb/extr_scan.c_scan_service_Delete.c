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
struct TYPE_4__ {struct TYPE_4__* psz_provider; struct TYPE_4__* psz_name; struct TYPE_4__* psz_original_network_name; } ;
typedef  TYPE_1__ scan_service_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void scan_service_Delete( scan_service_t *p_srv )
{
    free( p_srv->psz_original_network_name );
    free( p_srv->psz_name );
    free( p_srv->psz_provider );
    free( p_srv );
}