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
struct buf {scalar_t__ size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  bufput (struct buf*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
toc_link(struct buf *ob, const struct buf *link, const struct buf *title, const struct buf *content, void *opaque)
{
	if (content && content->size)
		bufput(ob, content->data, content->size);
	return 1;
}