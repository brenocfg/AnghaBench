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
 int /*<<< orphan*/  XML_ERR_FATAL ; 
 int /*<<< orphan*/  XML_ERR_NO_MEMORY ; 
 int /*<<< orphan*/  XML_FROM_URI ; 
 int /*<<< orphan*/  __xmlRaiseError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
xmlURIErrMemory(const char *extra)
{
    if (extra)
        __xmlRaiseError(NULL, NULL, NULL,
                        NULL, NULL, XML_FROM_URI,
                        XML_ERR_NO_MEMORY, XML_ERR_FATAL, NULL, 0,
                        extra, NULL, NULL, 0, 0,
                        "Memory allocation failed : %s\n", extra);
    else
        __xmlRaiseError(NULL, NULL, NULL,
                        NULL, NULL, XML_FROM_URI,
                        XML_ERR_NO_MEMORY, XML_ERR_FATAL, NULL, 0,
                        NULL, NULL, NULL, 0, 0,
                        "Memory allocation failed\n");
}