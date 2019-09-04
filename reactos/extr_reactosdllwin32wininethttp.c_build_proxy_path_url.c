#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* path; TYPE_1__* server; } ;
typedef  TYPE_2__ http_request_t ;
typedef  char WCHAR ;
struct TYPE_4__ {char* scheme_host_port; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  strcpyW (char*,char*) ; 
 int strlenW (char*) ; 

__attribute__((used)) static WCHAR *build_proxy_path_url(http_request_t *req)
{
    DWORD size, len;
    WCHAR *url;

    len = strlenW(req->server->scheme_host_port);
    size = len + strlenW(req->path) + 1;
    if(*req->path != '/')
        size++;
    url = heap_alloc(size * sizeof(WCHAR));
    if(!url)
        return NULL;

    memcpy(url, req->server->scheme_host_port, len*sizeof(WCHAR));
    if(*req->path != '/')
        url[len++] = '/';

    strcpyW(url+len, req->path);

    TRACE("url=%s\n", debugstr_w(url));
    return url;
}