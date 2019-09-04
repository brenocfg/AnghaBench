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

/* Variables and functions */
 int /*<<< orphan*/  XML_ERR_NO_MEMORY ; 
 int /*<<< orphan*/  XML_FROM_TREE ; 
 int /*<<< orphan*/  __xmlSimpleError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void
xmlTreeErrMemory(const char *extra)
{
    __xmlSimpleError(XML_FROM_TREE, XML_ERR_NO_MEMORY, NULL, NULL, extra);
}