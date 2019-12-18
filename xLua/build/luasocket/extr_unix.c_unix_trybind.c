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
typedef  TYPE_1__* p_unix ;
typedef  int /*<<< orphan*/  local ;
struct TYPE_3__ {int /*<<< orphan*/  sock; } ;
typedef  int /*<<< orphan*/  SA ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int IO_DONE ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 int socket_bind (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  socket_destroy (int /*<<< orphan*/ *) ; 
 char const* socket_strerror (int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static const char *unix_trybind(p_unix un, const char *path) {
    struct sockaddr_un local;
    size_t len = strlen(path);
    int err;
    if (len >= sizeof(local.sun_path)) return "path too long";
    memset(&local, 0, sizeof(local));
    strcpy(local.sun_path, path);
    local.sun_family = AF_UNIX;
#ifdef UNIX_HAS_SUN_LEN
    local.sun_len = sizeof(local.sun_family) + sizeof(local.sun_len) 
        + len + 1;
    err = socket_bind(&un->sock, (SA *) &local, local.sun_len);

#else 
    err = socket_bind(&un->sock, (SA *) &local, 
            sizeof(local.sun_family) + len);
#endif
    if (err != IO_DONE) socket_destroy(&un->sock);
    return socket_strerror(err); 
}