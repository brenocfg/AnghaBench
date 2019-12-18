#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_2__ {size_t recv_buf_len; int /*<<< orphan*/  recv_buf; } ;
typedef  TYPE_1__ MockConnection ;
typedef  int /*<<< orphan*/  Connection ;

/* Variables and functions */
 size_t MOCK_MAX_BUF_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,size_t) ; 

ssize_t
ts_connection_mock_set_recv_buf(Connection *conn, char *buf, size_t buf_len)
{
	MockConnection *mock = (MockConnection *) conn;

	if (buf_len > MOCK_MAX_BUF_SIZE)
		return -1;

	memcpy(mock->recv_buf, buf, buf_len);
	mock->recv_buf_len = buf_len;
	return mock->recv_buf_len;
}