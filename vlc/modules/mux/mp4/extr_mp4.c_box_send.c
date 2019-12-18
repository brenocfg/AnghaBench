#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  p_access; } ;
typedef  TYPE_1__ sout_mux_t ;
struct TYPE_7__ {scalar_t__ b; } ;
typedef  TYPE_2__ bo_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  sout_AccessOutWrite (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void box_send(sout_mux_t *p_mux,  bo_t *box)
{
    assert(box != NULL);
    if (box->b)
        sout_AccessOutWrite(p_mux->p_access, box->b);
    free(box);
}