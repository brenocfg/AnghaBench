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
typedef  int /*<<< orphan*/  object_header_t ;
typedef  int /*<<< orphan*/  connect_timeout ;
struct TYPE_2__ {int /*<<< orphan*/  agent; int /*<<< orphan*/  connect_timeout; } ;
typedef  TYPE_1__ appinfo_t ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int DWORD ;

/* Variables and functions */
 int ERROR_BAD_ARGUMENTS ; 
 int ERROR_INTERNET_BAD_OPTION_LENGTH ; 
 int ERROR_OUTOFMEMORY ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int INET_SetOption (int /*<<< orphan*/ *,int,void*,int) ; 
#define  INTERNET_OPTION_CONNECT_TIMEOUT 130 
#define  INTERNET_OPTION_REFRESH 129 
#define  INTERNET_OPTION_USER_AGENT 128 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_strdupW (void*) ; 

__attribute__((used)) static DWORD APPINFO_SetOption(object_header_t *hdr, DWORD option, void *buf, DWORD size)
{
    appinfo_t *ai = (appinfo_t*)hdr;

    switch(option) {
    case INTERNET_OPTION_CONNECT_TIMEOUT:
        TRACE("INTERNET_OPTION_CONNECT_TIMEOUT\n");

        if(size != sizeof(connect_timeout))
            return ERROR_INTERNET_BAD_OPTION_LENGTH;
        if(!*(ULONG*)buf)
            return ERROR_BAD_ARGUMENTS;

        ai->connect_timeout = *(ULONG*)buf;
        return ERROR_SUCCESS;
    case INTERNET_OPTION_USER_AGENT:
        heap_free(ai->agent);
        if (!(ai->agent = heap_strdupW(buf))) return ERROR_OUTOFMEMORY;
        return ERROR_SUCCESS;
    case INTERNET_OPTION_REFRESH:
        FIXME("INTERNET_OPTION_REFRESH\n");
        return ERROR_SUCCESS;
    }

    return INET_SetOption(hdr, option, buf, size);
}