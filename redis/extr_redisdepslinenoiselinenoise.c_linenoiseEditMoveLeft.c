#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct linenoiseState {scalar_t__ pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  refreshLine (struct linenoiseState*) ; 

void linenoiseEditMoveLeft(struct linenoiseState *l) {
    if (l->pos > 0) {
        l->pos--;
        refreshLine(l);
    }
}