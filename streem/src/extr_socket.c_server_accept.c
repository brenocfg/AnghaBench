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
struct socket_data {int /*<<< orphan*/  sock; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_4__ {struct socket_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  accept_cb ; 
 int /*<<< orphan*/  strm_io_start_read (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
server_accept(strm_stream* task, strm_value data)
{
  struct socket_data *sd = task->data;

  strm_io_start_read(task, sd->sock, accept_cb);
  return STRM_OK;
}