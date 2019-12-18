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
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_IO_NOWAIT ; 
 int /*<<< orphan*/  io_pop (int) ; 
 int /*<<< orphan*/  io_wait_num ; 
 int /*<<< orphan*/  strm_stream_close (TYPE_1__*) ; 

__attribute__((used)) static void
strm_io_stop(strm_stream* strm, int fd)
{
  if ((strm->flags & STRM_IO_NOWAIT) == 0) {
    io_wait_num--;
    io_pop(fd);
  }
  strm_stream_close(strm);
}