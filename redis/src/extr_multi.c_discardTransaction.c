#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; } ;
typedef  TYPE_1__ client ;

/* Variables and functions */
 int CLIENT_DIRTY_CAS ; 
 int CLIENT_DIRTY_EXEC ; 
 int CLIENT_MULTI ; 
 int /*<<< orphan*/  freeClientMultiState (TYPE_1__*) ; 
 int /*<<< orphan*/  initClientMultiState (TYPE_1__*) ; 
 int /*<<< orphan*/  unwatchAllKeys (TYPE_1__*) ; 

void discardTransaction(client *c) {
    freeClientMultiState(c);
    initClientMultiState(c);
    c->flags &= ~(CLIENT_MULTI|CLIENT_DIRTY_CAS|CLIENT_DIRTY_EXEC);
    unwatchAllKeys(c);
}