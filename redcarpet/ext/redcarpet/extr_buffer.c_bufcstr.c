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
struct buf {int size; int asize; scalar_t__* data; scalar_t__ unit; } ;

/* Variables and functions */
 scalar_t__ BUF_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bufgrow (struct buf const*,int) ; 

const char *
bufcstr(const struct buf *buf)
{
	assert(buf && buf->unit);

	if (buf->size < buf->asize && buf->data[buf->size] == 0)
		return (char *)buf->data;

	if (buf->size + 1 <= buf->asize || bufgrow(buf, buf->size + 1) == BUF_OK) {
		buf->data[buf->size] = 0;
		return (char *)buf->data;
	}

	return NULL;
}