#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fd_read_buffer {int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_3__ {struct fd_read_buffer* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct fd_read_buffer*) ; 

__attribute__((used)) static int
read_close(strm_stream* strm, strm_value d)
{
  struct fd_read_buffer *b = strm->data;

  close(b->fd);
  free(b);
  return STRM_OK;
}