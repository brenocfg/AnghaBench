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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {int /*<<< orphan*/  p_module; } ;
typedef  TYPE_1__ fingerprinter_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  module_need (TYPE_1__*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ vlc_custom_create (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_1__*) ; 

fingerprinter_thread_t *fingerprinter_Create( vlc_object_t *p_this )
{
    fingerprinter_thread_t *p_fingerprint;

    p_fingerprint = ( fingerprinter_thread_t * )
            vlc_custom_create( p_this, sizeof( *p_fingerprint ), "fingerprinter" );
    if( !p_fingerprint )
    {
        msg_Err( p_this, "unable to create fingerprinter" );
        return NULL;
    }

    p_fingerprint->p_module = module_need( p_fingerprint, "fingerprinter",
                                           NULL, false );
    if( !p_fingerprint->p_module )
    {
        vlc_object_delete(p_fingerprint);
        msg_Err( p_this, "AcoustID fingerprinter not found" );
        return NULL;
    }

    return p_fingerprint;
}