#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct strm_io {int dummy; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  TYPE_1__* strm_io ;
struct TYPE_4__ {int fd; int mode; int /*<<< orphan*/ * write_stream; int /*<<< orphan*/  read_stream; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  STRM_PTR_IO ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  strm_ptr_value (TYPE_1__*) ; 

strm_value
strm_io_new(int fd, int mode)
{
  strm_io io = malloc(sizeof(struct strm_io));

  io->fd = fd;
  io->mode = mode;
  io->type = STRM_PTR_IO;
  io->read_stream = io->write_stream = NULL;
  return strm_ptr_value(io);
}