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
struct TYPE_3__ {int /*<<< orphan*/  worker; int /*<<< orphan*/  deactivated; } ;
typedef  TYPE_1__ input_preparser_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  background_worker_Cancel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void input_preparser_Deactivate( input_preparser_t* preparser )
{
    atomic_store( &preparser->deactivated, true );
    background_worker_Cancel( preparser->worker, NULL );
}