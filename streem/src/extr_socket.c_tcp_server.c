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
struct socket_data {int sock; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; scalar_t__ ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; int /*<<< orphan*/  ai_flags; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_string ;
typedef  int /*<<< orphan*/  strm_stream ;
typedef  int /*<<< orphan*/  sockopt ;
typedef  int /*<<< orphan*/  WSADATA ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  AI_PASSIVE ; 
 int EAI_AGAIN ; 
 int /*<<< orphan*/  INVALID_SOCKET ; 
 int /*<<< orphan*/  MAKEWORD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_OPENTYPE ; 
 int SO_SYNCHRONOUS_NONALERT ; 
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (int /*<<< orphan*/ *,char const*,struct addrinfo*,struct addrinfo**) ; 
 scalar_t__ listen (int,int) ; 
 struct socket_data* malloc (int) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  server_accept ; 
 int /*<<< orphan*/  server_close ; 
 int /*<<< orphan*/  setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strm_number_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_producer ; 
 int /*<<< orphan*/  strm_raise (int /*<<< orphan*/ *,char*) ; 
 char* strm_str_cstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * strm_stream_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  strm_stream_value (int /*<<< orphan*/ *) ; 
 scalar_t__ strm_value_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_value_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tcp_server(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  int sock, s;
  strm_value srv;
  const char *service;
  char buf[12];
  struct socket_data *sd;
  strm_stream *t;

#ifdef _WIN32
  int sockopt = SO_SYNCHRONOUS_NONALERT;
  WSADATA wsa;
  WSAStartup(MAKEWORD(2, 0), &wsa);
  setsockopt(INVALID_SOCKET, SOL_SOCKET, SO_OPENTYPE, (char *)&sockopt, sizeof(sockopt));
#endif

  strm_get_args(strm, argc, args, "v", &srv);
  if (strm_number_p(srv)) {
    sprintf(buf, "%d", (int)strm_value_int(srv));
    service = buf;
  }
  else {
    strm_string str = strm_value_str(srv);
    service = strm_str_cstr(str, buf);
  }

  memset(&hints, 0, sizeof(struct addrinfo));
#ifdef _WIN32
  hints.ai_family = AF_INET;      /* TODO: IPv6 doesn't work on windows */
#else
  hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
#endif
  hints.ai_socktype = SOCK_STREAM;/* Datagram socket */
  hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
  hints.ai_protocol = 0;          /* Any protocol */

  for (;;) {
    s = getaddrinfo(NULL, service, &hints, &result);
    if (s != 0) {
      if (s == EAI_AGAIN) continue;
      strm_raise(strm, gai_strerror(s));
      return STRM_NG;
    }
    break;
  }

  for (rp = result; rp != NULL; rp = rp->ai_next) {
    sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (sock == -1) continue;

    if (bind(sock, rp->ai_addr, rp->ai_addrlen) == 0)
      break;                    /* Success */
    closesocket(sock);
  }

  freeaddrinfo(result);
  if (rp == NULL) {
    strm_raise(strm, "socket error: bind");
    return STRM_NG;
  }

  if (listen(sock, 5) < 0) {
    closesocket(sock);
    strm_raise(strm, "socket error: listen");
    return STRM_NG;
  }

  sd = malloc(sizeof(struct socket_data));
  sd->sock = sock;
  t = strm_stream_new(strm_producer, server_accept, server_close, (void*)sd);
  *ret = strm_stream_value(t);
  return STRM_OK;
}