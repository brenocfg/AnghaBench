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
typedef  char uint8_t ;
struct TYPE_2__ {scalar_t__ (* linebreak ) (struct buf*,int /*<<< orphan*/ ) ;} ;
struct sd_markdown {int /*<<< orphan*/  opaque; TYPE_1__ cb; } ;
struct buf {int size; char* data; } ;

/* Variables and functions */
 scalar_t__ stub1 (struct buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
char_linebreak(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t offset, size_t size)
{
	if (offset < 2 || data[-1] != ' ' || data[-2] != ' ')
		return 0;

	/* removing the last space from ob and rendering */
	while (ob->size && ob->data[ob->size - 1] == ' ')
		ob->size--;

	return rndr->cb.linebreak(ob, rndr->opaque) ? 1 : 0;
}