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
struct buf {int dummy; } ;
typedef  enum mkd_autolink { ____Placeholder_mkd_autolink } mkd_autolink ;

/* Variables and functions */
 int /*<<< orphan*/  CSTR2SYM (char*) ; 
 int MKDA_NORMAL ; 
 int /*<<< orphan*/  SPAN_CALLBACK (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf2str (struct buf const*) ; 

__attribute__((used)) static int
rndr_autolink(struct buf *ob, const struct buf *link, enum mkd_autolink type, void *opaque)
{
	SPAN_CALLBACK("autolink", 2, buf2str(link),
		type == MKDA_NORMAL ? CSTR2SYM("url") : CSTR2SYM("email"));
}