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
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  psz_sout; int /*<<< orphan*/  p_stream; } ;
typedef  TYPE_1__ sout_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREENULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sout_StreamChainDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_1__*) ; 

void sout_DeleteInstance( sout_instance_t * p_sout )
{
    /* remove the stream out chain */
    sout_StreamChainDelete( p_sout->p_stream, NULL );

    /* *** free all string *** */
    FREENULL( p_sout->psz_sout );

    vlc_mutex_destroy( &p_sout->lock );

    /* *** free structure *** */
    vlc_object_delete(p_sout);
}