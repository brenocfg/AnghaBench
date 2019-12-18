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
typedef  int /*<<< orphan*/  Query ;
typedef  int /*<<< orphan*/  ParseState ;

/* Variables and functions */
 int /*<<< orphan*/  extension_post_parse_analyze_hook (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ loaded ; 

__attribute__((used)) static void
call_extension_post_parse_analyze_hook(ParseState *pstate, Query *query)
{
	if (loaded && extension_post_parse_analyze_hook != NULL)
	{
		extension_post_parse_analyze_hook(pstate, query);
	}
}