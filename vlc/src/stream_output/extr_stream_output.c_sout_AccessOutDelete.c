#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  psz_path; int /*<<< orphan*/  p_cfg; int /*<<< orphan*/  psz_access; scalar_t__ p_module; } ;
typedef  TYPE_1__ sout_access_out_t ;

/* Variables and functions */
 int /*<<< orphan*/  config_ChainDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_unneed (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_1__*) ; 

void sout_AccessOutDelete( sout_access_out_t *p_access )
{
    if( p_access->p_module )
    {
        module_unneed( p_access, p_access->p_module );
    }
    free( p_access->psz_access );

    config_ChainDestroy( p_access->p_cfg );

    free( p_access->psz_path );

    vlc_object_delete(p_access);
}