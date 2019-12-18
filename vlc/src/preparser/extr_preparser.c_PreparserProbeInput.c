#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  done; } ;
typedef  TYPE_1__ input_preparser_task_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (void*) ; 
 int atomic_load (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int PreparserProbeInput( void* preparser_, void* task_ )
{
    input_preparser_task_t* task = task_;
    return atomic_load( &task->done );
    VLC_UNUSED( preparser_ );
}