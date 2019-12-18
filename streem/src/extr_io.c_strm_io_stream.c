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
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;
typedef  int /*<<< orphan*/  strm_io ;

/* Variables and functions */
#define  STRM_IO_READ 129 
#define  STRM_IO_WRITE 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_io_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strm_readio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_value_io (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strm_writeio (int /*<<< orphan*/ ) ; 

strm_stream*
strm_io_stream(strm_value iov, int mode)
{
  strm_io io;

  assert(strm_io_p(iov));
  io = strm_value_io(iov);
  switch (mode) {
  case STRM_IO_READ:
    return strm_readio(io);
  case STRM_IO_WRITE:
    return strm_writeio(io);
 default:
   return NULL;
  }
}