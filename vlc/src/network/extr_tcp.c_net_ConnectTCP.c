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
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ SocksHandshakeTCP (int /*<<< orphan*/ *,int,int,char*,char*,char const*,int) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char const*,int,...) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  net_Close (int) ; 
 int net_Connect (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 char* var_InheritString (int /*<<< orphan*/ *,char*) ; 

int (net_ConnectTCP)(vlc_object_t *obj, const char *host, int serv)
{
    const char *realhost;
    int realserv;

    char *socks = var_InheritString(obj, "socks");
    if (socks != NULL)
    {
        realhost = socks;

        char *p = strchr(socks, ':');
        if (p != NULL)
        {
            *(p++) = '\0';
            realserv = atoi(p);
        }
        else
            realserv = 1080;

        msg_Dbg(obj, "net: connecting to %s port %d (SOCKS) "
                "for %s port %d", realhost, realserv, host, serv);
    }
    else
    {
        msg_Dbg(obj, "net: connecting to %s port %d", host, serv);
        realhost = host;
        realserv = serv;
    }

    int fd = net_Connect(obj, realhost, realserv, SOCK_STREAM, IPPROTO_TCP);

    if (socks != NULL && fd != -1)
    {
        /* NOTE: psz_socks already free'd! */
        char *user = var_InheritString(obj, "socks-user");
        char *pwd = var_InheritString(obj, "socks-pwd");

        if (SocksHandshakeTCP(obj, fd, 5, user, pwd, host, serv))
        {
            msg_Err(obj, "SOCKS handshake failed");
            net_Close(fd);
            fd = -1;
        }

        free(pwd);
        free(user);
    }

    return fd;
}