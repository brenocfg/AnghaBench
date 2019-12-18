#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ current_level; } ;
struct html_renderopt {TYPE_1__ toc_data; } ;
struct buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFPUTSL (struct buf*,char*) ; 

__attribute__((used)) static void
toc_finalize(struct buf *ob, void *opaque)
{
	struct html_renderopt *options = opaque;

	while (options->toc_data.current_level > 0) {
		BUFPUTSL(ob, "</li>\n</ul>\n");
		options->toc_data.current_level--;
	}
}