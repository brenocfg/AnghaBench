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
struct call_entry {int /*<<< orphan*/  column; int /*<<< orphan*/  line; } ;
typedef  int /*<<< orphan*/  ISAXLocator ;

/* Variables and functions */
 int /*<<< orphan*/  ISAXLocator_getColumnNumber (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISAXLocator_getLineNumber (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct call_entry*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_call_entry(ISAXLocator *locator, struct call_entry *call)
{
    memset(call, 0, sizeof(*call));
    ISAXLocator_getLineNumber(locator, &call->line);
    ISAXLocator_getColumnNumber(locator, &call->column);
}