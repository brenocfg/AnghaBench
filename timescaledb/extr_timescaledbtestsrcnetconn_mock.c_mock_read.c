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
typedef  size_t ssize_t ;
struct TYPE_2__ {scalar_t__ recv_buf_offset; scalar_t__ recv_buf_len; size_t recv_buf; } ;
typedef  TYPE_1__ MockConnection ;
typedef  int /*<<< orphan*/  Connection ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,size_t,size_t) ; 
 size_t rand () ; 

__attribute__((used)) static ssize_t
mock_read(Connection *conn, char *buf, size_t readlen)
{
	size_t bytes_to_read = 0;
	size_t max = readlen;
	MockConnection *mock = (MockConnection *) conn;

	if (mock->recv_buf_offset >= mock->recv_buf_len)
		return 0;

	if (max >= mock->recv_buf_len - mock->recv_buf_offset)
		max = mock->recv_buf_len - mock->recv_buf_offset;

	/* Now read a random amount */
	while (bytes_to_read == 0)
	{
		bytes_to_read = rand() % (max + 1);
	}
	memcpy(buf, mock->recv_buf + mock->recv_buf_offset, bytes_to_read);
	mock->recv_buf_offset += bytes_to_read;

	return bytes_to_read;
}