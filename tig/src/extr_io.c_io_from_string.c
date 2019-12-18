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
struct io {size_t bufalloc; size_t bufsize; int eof; int /*<<< orphan*/  buf; int /*<<< orphan*/  bufpos; } ;

/* Variables and functions */
 int /*<<< orphan*/  io_init (struct io*) ; 
 int /*<<< orphan*/  io_realloc_buf (int /*<<< orphan*/ *,size_t,size_t) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,size_t) ; 

bool
io_from_string(struct io *io, const char *str)
{
	size_t len = strlen(str);

	io_init(io);

	if (!io_realloc_buf(&io->buf, io->bufalloc, len))
		return false;

	io->bufsize = io->bufalloc = len;
	io->bufpos = io->buf;
	io->eof = true;
	strncpy(io->buf, str, len);

	return true;
}