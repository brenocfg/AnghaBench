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
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; int /*<<< orphan*/  ai_flags; } ;
typedef  int /*<<< orphan*/  strport ;
struct TYPE_4__ {int sock; int err; } ;
typedef  TYPE_1__ Connection ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  AI_NUMERICSERV ; 
 int /*<<< orphan*/  DEFAULT_TIMEOUT_MSEC ; 
 int /*<<< orphan*/  EADDRNOTAVAIL ; 
 int /*<<< orphan*/  EINVAL ; 
 int INVALID_SOCKET ; 
 scalar_t__ IS_SOCKET_ERROR (int) ; 
 int MAX_PORT ; 
 int SOCKET_ERROR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int WSAConnect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WSAHOST_NOT_FOUND ; 
 int /*<<< orphan*/  WSASetLastError (int /*<<< orphan*/ ) ; 
 int WSASocket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSA_FLAG_OVERLAPPED ; 
 int connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int getaddrinfo (char const*,char const*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ts_plain_set_timeout (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
ts_plain_connect(Connection *conn, const char *host, const char *servname, int port)
{
	char strport[6];
	struct addrinfo *ainfo, hints = {
		.ai_family = AF_UNSPEC,
		.ai_socktype = SOCK_STREAM,
	};
	int ret;

	if (NULL == servname && (port <= 0 || port > MAX_PORT))
	{
		set_error(EINVAL);
		return -1;
	}

	/* Explicit port given. Use it instead of servname */
	if (port > 0 && port <= MAX_PORT)
	{
		snprintf(strport, sizeof(strport), "%d", port);
		servname = strport;
		hints.ai_flags = AI_NUMERICSERV;
	}

	/* Lookup the endpoint ip address */
	ret = getaddrinfo(host, servname, &hints, &ainfo);

	if (ret != 0)
	{
		ret = SOCKET_ERROR;

#ifdef WIN32
		WSASetLastError(WSAHOST_NOT_FOUND);
#else

		/*
		 * The closest match for a name resolution error. Strictly, this error
		 * should not be used here, but to fix we need to support using
		 * gai_strerror()
		 */
		errno = EADDRNOTAVAIL;
#endif
		goto out;
	}

#ifdef WIN32

	/*
	 * PostgreSQL redefines the socket() call on Windows and creates a
	 * non-blocking socket by default. We avoid this by calling WSASocket
	 * directly.
	 */
	conn->sock = WSASocket(ainfo->ai_family,
						   ainfo->ai_socktype,
						   ainfo->ai_protocol,
						   NULL,
						   0,
						   WSA_FLAG_OVERLAPPED);

	if (conn->sock == INVALID_SOCKET)
		ret = SOCKET_ERROR;
#else
	ret = conn->sock = socket(ainfo->ai_family, ainfo->ai_socktype, ainfo->ai_protocol);
#endif

	if (IS_SOCKET_ERROR(ret))
		goto out_addrinfo;

	/*
	 * Set send / recv timeout so that write and read don't block forever. Set
	 * separately so that one of the actions failing doesn't block the other.
	 */
	if (ts_plain_set_timeout(conn, DEFAULT_TIMEOUT_MSEC) < 0)
	{
		ret = SOCKET_ERROR;
		goto out_addrinfo;
	}

#ifdef WIN32
	ret = WSAConnect(conn->sock, ainfo->ai_addr, ainfo->ai_addrlen, NULL, NULL, NULL, NULL);
#else
	/* connect the socket */
	ret = connect(conn->sock, ainfo->ai_addr, ainfo->ai_addrlen);
#endif

out_addrinfo:
	freeaddrinfo(ainfo);

out:
	if (IS_SOCKET_ERROR(ret))
	{
		conn->err = ret;
		return -1;
	}

	return 0;
}