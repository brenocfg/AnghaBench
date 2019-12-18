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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  remote_name ;
typedef  int /*<<< orphan*/  net_resource ;
struct TYPE_4__ {int /*<<< orphan*/ * lpRemoteName; int /*<<< orphan*/  dwType; } ;
typedef  TYPE_1__ NETRESOURCE ;

/* Variables and functions */
#define  ERROR_ALREADY_ASSIGNED 130 
#define  ERROR_DEVICE_ALREADY_REMEMBERED 129 
 int MAX_PATH ; 
#define  NO_ERROR 128 
 int /*<<< orphan*/  RESOURCETYPE_DISK ; 
 int /*<<< orphan*/ * ToWide (char const*) ; 
 int WNetAddConnection2 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void Win32AddConnection(stream_t *access, const char *server,
                               const char *share, const char *user,
                               const char *pwd)
{
    NETRESOURCE net_resource;
    char remote_name[MAX_PATH];

    memset(&net_resource, 0, sizeof (net_resource));
    net_resource.dwType = RESOURCETYPE_DISK;

    snprintf(remote_name, sizeof (remote_name), "\\\\%s\\%s", server,
             (share != NULL) ? share + 1 /* skip leading '/' */: "");

    /* remove trailings '/' */
    char *delim = strchr(remote_name, '/');
    if (delim != NULL)
        *delim = '\0';

    const char *msg;
    net_resource.lpRemoteName = ToWide(remote_name);

    wchar_t *wpwd  = pwd  ? ToWide(pwd)  : NULL;
    wchar_t *wuser = user ? ToWide(user) : NULL;

    switch (WNetAddConnection2(&net_resource, wpwd, wuser, 0))
    {
        case NO_ERROR:
            msg = "connected to %s";
            break;
        case ERROR_ALREADY_ASSIGNED:
        case ERROR_DEVICE_ALREADY_REMEMBERED:
            msg = "already connected to %s";
            break;
        default:
            msg = "failed to connect to %s";
    }
    free(net_resource.lpRemoteName);
    free(wpwd);
    free(wuser);
    msg_Dbg(access, msg, remote_name);
}