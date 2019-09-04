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
struct TYPE_3__ {char* name; char* scheme_host_port; char* host_port; char* canon_host_port; scalar_t__ is_https; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ server_t ;
typedef  int /*<<< orphan*/  httpsW ;
typedef  char WCHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  INTERNET_DEFAULT_HTTPS_PORT ; 
 int /*<<< orphan*/  INTERNET_DEFAULT_HTTP_PORT ; 
 int TRUE ; 
 char* heap_alloc (size_t) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,char const*,char*,int /*<<< orphan*/ ) ; 
 size_t strlenW (char*) ; 

__attribute__((used)) static BOOL process_host_port(server_t *server)
{
    BOOL default_port;
    size_t name_len;
    WCHAR *buf;

    static const WCHAR httpW[] = {'h','t','t','p',0};
    static const WCHAR httpsW[] = {'h','t','t','p','s',0};
    static const WCHAR formatW[] = {'%','s',':','/','/','%','s',':','%','u',0};

    name_len = strlenW(server->name);
    buf = heap_alloc((name_len + 10 /* strlen("://:<port>") */)*sizeof(WCHAR) + sizeof(httpsW));
    if(!buf)
        return FALSE;

    sprintfW(buf, formatW, server->is_https ? httpsW : httpW, server->name, server->port);
    server->scheme_host_port = buf;

    server->host_port = server->scheme_host_port + 7 /* strlen("http://") */;
    if(server->is_https)
        server->host_port++;

    default_port = server->port == (server->is_https ? INTERNET_DEFAULT_HTTPS_PORT : INTERNET_DEFAULT_HTTP_PORT);
    server->canon_host_port = default_port ? server->name : server->host_port;
    return TRUE;
}