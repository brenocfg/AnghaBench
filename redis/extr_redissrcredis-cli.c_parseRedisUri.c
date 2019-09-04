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
struct TYPE_2__ {void* dbnum; int /*<<< orphan*/  hostip; void* hostport; int /*<<< orphan*/  auth; } ;

/* Variables and functions */
 void* atoi (char const*) ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  percentDecode (char const*,int) ; 
 int /*<<< orphan*/  sdsnewlen (char const*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char const*,int) ; 

__attribute__((used)) static void parseRedisUri(const char *uri) {

    const char *scheme = "redis://";
    const char *curr = uri;
    const char *end = uri + strlen(uri);
    const char *userinfo, *username, *port, *host, *path;

    /* URI must start with a valid scheme. */
    if (strncasecmp(scheme, curr, strlen(scheme))) {
        fprintf(stderr,"Invalid URI scheme\n");
        exit(1);
    }
    curr += strlen(scheme);
    if (curr == end) return;

    /* Extract user info. */
    if ((userinfo = strchr(curr,'@'))) {
        if ((username = strchr(curr, ':')) && username < userinfo) {
            /* If provided, username is ignored. */
            curr = username + 1;
        }

        config.auth = percentDecode(curr, userinfo - curr);
        curr = userinfo + 1;
    }
    if (curr == end) return;

    /* Extract host and port. */
    path = strchr(curr, '/');
    if (*curr != '/') {
        host = path ? path - 1 : end;
        if ((port = strchr(curr, ':'))) {
            config.hostport = atoi(port + 1);
            host = port - 1;
        }
        config.hostip = sdsnewlen(curr, host - curr + 1);
    }
    curr = path ? path + 1 : end;
    if (curr == end) return;

    /* Extract database number. */
    config.dbnum = atoi(curr);
}