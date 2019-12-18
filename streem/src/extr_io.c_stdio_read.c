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
struct fd_read_buffer {int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_4__ {struct fd_read_buffer* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  read_cb ; 
 int /*<<< orphan*/  strm_io_start_read (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
stdio_read(strm_stream* strm, strm_value data)
{
  struct fd_read_buffer *b = strm->data;

  strm_io_start_read(strm, b->fd, read_cb);
  return STRM_OK;
}