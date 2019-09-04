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
struct run_request {int dummy; } ;
typedef  enum request { ____Placeholder_request } request ;

/* Variables and functions */
 int REQ_NONE ; 
 int exec_run_request (struct view*,struct run_request*) ; 
 struct run_request* get_run_request (int) ; 
 int /*<<< orphan*/  report (char*) ; 

__attribute__((used)) static enum request
open_run_request(struct view *view, enum request request)
{
	struct run_request *req = get_run_request(request);

	if (!req) {
		report("Unknown run request");
		return REQ_NONE;
	}

	return exec_run_request(view, req);
}