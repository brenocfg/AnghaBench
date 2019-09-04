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
struct linenoiseState {int dummy; } ;

/* Variables and functions */
 scalar_t__ mlmode ; 
 int /*<<< orphan*/  refreshMultiLine (struct linenoiseState*) ; 
 int /*<<< orphan*/  refreshSingleLine (struct linenoiseState*) ; 

__attribute__((used)) static void refreshLine(struct linenoiseState *l) {
    if (mlmode)
        refreshMultiLine(l);
    else
        refreshSingleLine(l);
}