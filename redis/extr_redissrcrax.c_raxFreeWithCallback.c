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
struct TYPE_5__ {scalar_t__ numnodes; int /*<<< orphan*/  head; } ;
typedef  TYPE_1__ rax ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  raxRecursiveFree (TYPE_1__*,int /*<<< orphan*/ ,void (*) (void*)) ; 
 int /*<<< orphan*/  rax_free (TYPE_1__*) ; 

void raxFreeWithCallback(rax *rax, void (*free_callback)(void*)) {
    raxRecursiveFree(rax,rax->head,free_callback);
    assert(rax->numnodes == 0);
    rax_free(rax);
}