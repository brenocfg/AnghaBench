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
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; scalar_t__ ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_string ;
typedef  int /*<<< orphan*/  strm_stream ;
typedef  int /*<<< orphan*/  WSADATA ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  MAKEWORD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int STRM_IO_FLUSH ; 
 int STRM_IO_READ ; 
 int STRM_IO_WRITE ; 
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 int connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (char*,char const*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_io_new (int,int) ; 
 scalar_t__ strm_number_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_raise (int /*<<< orphan*/ *,char*) ; 
 char* strm_str_cstr (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strm_value_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_value_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tcp_socket(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  int sock, s;
  const char *service;
  char sbuf[12], hbuf[7];
  strm_string host;
  strm_value srv;

#ifdef _WIN32
  WSADATA wsa;
  WSAStartup(MAKEWORD(2, 0), &wsa);
#endif

  strm_get_args(strm, argc, args, "Sv", &host, &srv);
  if (strm_number_p(srv)) {
    sprintf(sbuf, "%d", (int)strm_value_int(srv));
    service = sbuf;
  }
  else {
    strm_string str = strm_value_str(srv);
    service = strm_str_cstr(str, sbuf);
  }

  memset(&hints, 0, sizeof(struct addrinfo));
#ifdef _WIN32
  hints.ai_family = AF_INET;      /* TODO: IPv6 doesn't work on windows */
#else
  hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
#endif
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = 0;          /* Any protocol */
  s = getaddrinfo(strm_str_cstr(host, hbuf), service, &hints, &result);

  if (s != 0) {
    strm_raise(strm, gai_strerror(s));
    return STRM_NG;
  }

  for (rp = result; rp != NULL; rp = rp->ai_next) {
    sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (sock == -1) continue;

    if (connect(sock, rp->ai_addr, rp->ai_addrlen) != -1)
      break;                    /* Success */
    closesocket(sock);
  }

  freeaddrinfo(result);
  if (rp == NULL) {
    strm_raise(strm, "socket error: connect");
    return STRM_NG;
  }
  *ret = strm_io_new(sock, STRM_IO_READ|STRM_IO_WRITE|STRM_IO_FLUSH);
  return STRM_OK;
}