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
struct TYPE_4__ {int /*<<< orphan*/  next; int /*<<< orphan*/  current; } ;
typedef  TYPE_1__ cc_storage_t ;

/* Variables and functions */
 int /*<<< orphan*/  cc_Exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void cc_storage_delete( cc_storage_t *p_ccs )
{
    cc_Exit( &p_ccs->current );
    cc_Exit( &p_ccs->next );
    free( p_ccs );
}