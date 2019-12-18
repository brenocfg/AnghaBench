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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  private_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  CommonClose (int /*<<< orphan*/ *) ; 
 scalar_t__ archive_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ probe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * setup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static private_sys_t* CommonOpen( vlc_object_t* p_obj, stream_t* source  )
{
    if( probe( source ) )
        return NULL;

    private_sys_t* p_sys = setup( p_obj, source );

    if( p_sys == NULL )
        return NULL;

    if( archive_init( p_sys, source ) )
    {
        CommonClose( p_sys );
        return NULL;
    }

    return p_sys;
}