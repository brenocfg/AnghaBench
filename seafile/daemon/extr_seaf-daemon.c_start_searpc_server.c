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
struct TYPE_2__ {char* rpc_socket_path; int /*<<< orphan*/  seaf_dir; } ;
typedef  int /*<<< orphan*/  SearpcNamedPipeServer ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ GetUserName (char*,int*) ; 
 int /*<<< orphan*/  SEAFILE_SOCKET_NAME ; 
 int /*<<< orphan*/  b64encode (char*) ; 
 char* g_build_filename (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_rpc_service () ; 
 TYPE_1__* seaf ; 
 int /*<<< orphan*/  seaf_warning (char*,...) ; 
 int /*<<< orphan*/ * searpc_create_named_pipe_server (char*) ; 
 int searpc_named_pipe_server_start (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
start_searpc_server ()
{
    register_rpc_service ();

#ifdef WIN32
    DWORD bufCharCount = 32767;
    char userNameBuf[bufCharCount];
    if (GetUserName(userNameBuf, &bufCharCount) == 0) {
        seaf_warning ("Failed to get user name, GLE=%lu, required size is %lu\n",
                      GetLastError(), bufCharCount);
        return -1;
    }

    char *path = g_strdup_printf("\\\\.\\pipe\\seafile_%s", b64encode(userNameBuf));
#else
    char *path = g_build_filename (seaf->seaf_dir, SEAFILE_SOCKET_NAME, NULL);
#endif

    SearpcNamedPipeServer *server = searpc_create_named_pipe_server (path);
    if (!server) {
        seaf_warning ("Failed to create named pipe server.\n");
        g_free (path);
        return -1;
    }

    seaf->rpc_socket_path = path;

    return searpc_named_pipe_server_start (server);
}