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
struct view {int dummy; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;
typedef  enum request { ____Placeholder_request } request ;

/* Variables and functions */
 int find_next_merge (struct view*,int) ; 
 int /*<<< orphan*/  get_status_message (int) ; 
 int /*<<< orphan*/  report (char*,int /*<<< orphan*/ ) ; 

void
find_merge(struct view *view, enum request request)
{
	enum status_code code = find_next_merge(view, request);

	report("%s", get_status_message(code));
}