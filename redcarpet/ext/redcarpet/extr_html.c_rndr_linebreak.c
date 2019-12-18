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
struct html_renderopt {int dummy; } ;
struct buf {int dummy; } ;

/* Variables and functions */
 scalar_t__ USE_XHTML (struct html_renderopt*) ; 
 int /*<<< orphan*/  bufputs (struct buf*,char*) ; 

__attribute__((used)) static int
rndr_linebreak(struct buf *ob, void *opaque)
{
	struct html_renderopt *options = opaque;
	bufputs(ob, USE_XHTML(options) ? "<br/>\n" : "<br>\n");
	return 1;
}