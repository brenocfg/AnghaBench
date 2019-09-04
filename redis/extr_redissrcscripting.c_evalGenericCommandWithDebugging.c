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
typedef  int /*<<< orphan*/  client ;

/* Variables and functions */
 int /*<<< orphan*/  evalGenericCommand (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldbDisable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldbEndSession (int /*<<< orphan*/ *) ; 
 scalar_t__ ldbStartSession (int /*<<< orphan*/ *) ; 

void evalGenericCommandWithDebugging(client *c, int evalsha) {
    if (ldbStartSession(c)) {
        evalGenericCommand(c,evalsha);
        ldbEndSession(c);
    } else {
        ldbDisable(c);
    }
}