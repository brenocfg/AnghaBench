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
struct buf {int size; int asize; int* data; scalar_t__ unit; } ;

/* Variables and functions */
 scalar_t__ BUF_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bufgrow (struct buf*,int) ; 

void
bufputc(struct buf *buf, int c)
{
	assert(buf && buf->unit);

	if (buf->size + 1 > buf->asize && bufgrow(buf, buf->size + 1) < BUF_OK)
		return;

	buf->data[buf->size] = c;
	buf->size += 1;
}