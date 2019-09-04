#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sock; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ssl; TYPE_1__ conn; int /*<<< orphan*/ * ssl_ctx; } ;
typedef  TYPE_2__ SSLConnection ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_clear_error () ; 
 int SSL_connect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ *) ; 
 int SSL_set_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ssl_ctx_create () ; 
 int /*<<< orphan*/  ssl_set_error (TYPE_2__*,int) ; 

__attribute__((used)) static int
ssl_setup(SSLConnection *conn)
{
	int ret;

	conn->ssl_ctx = ssl_ctx_create();

	if (NULL == conn->ssl_ctx)
	{
		ssl_set_error(conn, -1);
		return -1;
	}

	ERR_clear_error();

	conn->ssl = SSL_new(conn->ssl_ctx);

	if (conn->ssl == NULL)
	{
		ssl_set_error(conn, -1);
		return -1;
	}

	ERR_clear_error();

	ret = SSL_set_fd(conn->ssl, conn->conn.sock);

	if (ret == 0)
	{
		ssl_set_error(conn, -1);
		return -1;
	}

	ret = SSL_connect(conn->ssl);

	if (ret <= 0)
	{
		ssl_set_error(conn, ret);
		ret = -1;
	}

	return ret;
}