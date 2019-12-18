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
struct sockaddr_un {int sun_len; int /*<<< orphan*/  sun_family; int /*<<< orphan*/  sun_path; } ;
typedef  int /*<<< orphan*/  remote ;
typedef  TYPE_1__* p_unix ;
struct TYPE_3__ {int /*<<< orphan*/  sock; int /*<<< orphan*/  tm; } ;
typedef  int /*<<< orphan*/  SA ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int IO_DONE ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 int socket_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socket_destroy (int /*<<< orphan*/ *) ; 
 char const* socket_strerror (int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  timeout_markstart (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *unix_tryconnect(p_unix un, const char *path)
{
    struct sockaddr_un remote;
    int err;
    size_t len = strlen(path);
    if (len >= sizeof(remote.sun_path)) return "path too long";
    memset(&remote, 0, sizeof(remote));
    strcpy(remote.sun_path, path);
    remote.sun_family = AF_UNIX;
    timeout_markstart(&un->tm);
#ifdef UNIX_HAS_SUN_LEN
    remote.sun_len = sizeof(remote.sun_family) + sizeof(remote.sun_len) 
        + len + 1;
    err = socket_connect(&un->sock, (SA *) &remote, remote.sun_len, &un->tm);
#else
    err = socket_connect(&un->sock, (SA *) &remote, 
            sizeof(remote.sun_family) + len, &un->tm);
#endif
    if (err != IO_DONE) socket_destroy(&un->sock);
    return socket_strerror(err);
}