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
struct TYPE_3__ {scalar_t__ key; scalar_t__ key_static_string; int /*<<< orphan*/  stack; } ;
typedef  TYPE_1__ raxIterator ;

/* Variables and functions */
 int /*<<< orphan*/  raxStackFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rax_free (scalar_t__) ; 

void raxStop(raxIterator *it) {
    if (it->key != it->key_static_string) rax_free(it->key);
    raxStackFree(&it->stack);
}