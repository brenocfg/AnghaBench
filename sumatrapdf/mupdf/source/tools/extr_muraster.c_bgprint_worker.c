#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ fz_cookie ;
typedef  int /*<<< orphan*/  cookie ;
struct TYPE_6__ {int pagenum; int /*<<< orphan*/  stop; int /*<<< orphan*/  render; int /*<<< orphan*/  solo; int /*<<< orphan*/  filename; int /*<<< orphan*/  interptime; int /*<<< orphan*/  ctx; int /*<<< orphan*/  status; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_THREADS (char*) ; 
 TYPE_4__ bgprint ; 
 int gettime () ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mu_trigger_semaphore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mu_wait_semaphore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_render_page (int /*<<< orphan*/ ,int,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bgprint_worker(void *arg)
{
	fz_cookie cookie = { 0 };
	int pagenum;

	(void)arg;

	do
	{
		DEBUG_THREADS(("BGPrint waiting\n"));
		mu_wait_semaphore(&bgprint.start);
		pagenum = bgprint.pagenum;
		DEBUG_THREADS(("BGPrint woken for pagenum %d\n", pagenum));
		if (pagenum >= 0)
		{
			int start = gettime();
			memset(&cookie, 0, sizeof(cookie));
			bgprint.status = try_render_page(bgprint.ctx, pagenum, &cookie, start, bgprint.interptime, bgprint.filename, 1, bgprint.solo, &bgprint.render);
		}
		DEBUG_THREADS(("BGPrint completed page %d\n", pagenum));
		mu_trigger_semaphore(&bgprint.stop);
	}
	while (pagenum >= 0);
}