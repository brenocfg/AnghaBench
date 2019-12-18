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
typedef  int /*<<< orphan*/  xmlNodePtr ;

/* Variables and functions */
 int xmlXPathCmpNodesExt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wrap_cmp( xmlNodePtr x, xmlNodePtr y )
    {
        int res = xmlXPathCmpNodesExt(x, y);
        return res == -2 ? res : -res;
    }