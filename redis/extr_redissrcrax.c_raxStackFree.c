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
struct TYPE_3__ {scalar_t__ stack; scalar_t__ static_items; } ;
typedef  TYPE_1__ raxStack ;

/* Variables and functions */
 int /*<<< orphan*/  rax_free (scalar_t__) ; 

__attribute__((used)) static inline void raxStackFree(raxStack *ts) {
    if (ts->stack != ts->static_items) rax_free(ts->stack);
}