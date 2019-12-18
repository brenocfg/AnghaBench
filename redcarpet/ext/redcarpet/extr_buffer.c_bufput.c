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
struct buf {scalar_t__ size; scalar_t__ asize; scalar_t__ data; scalar_t__ unit; } ;

/* Variables and functions */
 scalar_t__ BUF_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bufgrow (struct buf*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,size_t) ; 

void
bufput(struct buf *buf, const void *data, size_t len)
{
	assert(buf && buf->unit);

	if (buf->size + len > buf->asize && bufgrow(buf, buf->size + len) < BUF_OK)
		return;

	memcpy(buf->data + buf->size, data, len);
	buf->size += len;
}