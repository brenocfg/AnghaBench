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
struct TYPE_4__ {scalar_t__ fetcher; int /*<<< orphan*/  worker; } ;
typedef  TYPE_1__ input_preparser_t ;

/* Variables and functions */
 int /*<<< orphan*/  background_worker_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  input_fetcher_Delete (scalar_t__) ; 

void input_preparser_Delete( input_preparser_t *preparser )
{
    background_worker_Delete( preparser->worker );

    if( preparser->fetcher )
        input_fetcher_Delete( preparser->fetcher );

    free( preparser );
}