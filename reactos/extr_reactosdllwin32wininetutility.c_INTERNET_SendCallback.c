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
struct TYPE_3__ {int dwInternalFlags; int /*<<< orphan*/  hInternet; int /*<<< orphan*/  (* lpfnStatusCB ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*,int) ;} ;
typedef  TYPE_1__ object_header_t ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int DWORD ;

/* Variables and functions */
 int INET_CALLBACKW ; 
#define  INTERNET_STATUS_CONNECTED_TO_SERVER 132 
#define  INTERNET_STATUS_CONNECTING_TO_SERVER 131 
#define  INTERNET_STATUS_NAME_RESOLVED 130 
#define  INTERNET_STATUS_REDIRECT 129 
#define  INTERNET_STATUS_RESOLVING_NAME 128 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  debugstr_status_info (int,void*) ; 
 int /*<<< orphan*/  get_callback_name (int) ; 
 void* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (void*) ; 
 void* heap_strdupW (void*) ; 
 void* heap_strdupWtoA (void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  strlen (void*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*,int) ; 

void INTERNET_SendCallback(object_header_t *hdr, DWORD_PTR context, DWORD status, void *info, DWORD info_len)
{
    void *new_info = info;

    if( !hdr->lpfnStatusCB )
        return;

    /* the IE5 version of wininet does not
       send callbacks if dwContext is zero */
    if(!context)
        return;

    switch(status) {
    case INTERNET_STATUS_NAME_RESOLVED:
    case INTERNET_STATUS_CONNECTING_TO_SERVER:
    case INTERNET_STATUS_CONNECTED_TO_SERVER:
        new_info = heap_alloc(info_len);
        if(new_info)
            memcpy(new_info, info, info_len);
        break;
    case INTERNET_STATUS_RESOLVING_NAME:
    case INTERNET_STATUS_REDIRECT:
        if(hdr->dwInternalFlags & INET_CALLBACKW) {
            new_info = heap_strdupW(info);
            break;
        }else {
            new_info = heap_strdupWtoA(info);
            info_len = strlen(new_info)+1;
            break;
        }
    }
    
    TRACE(" callback(%p) (%p (%p), %08lx, %d (%s), %s, %d)\n",
	  hdr->lpfnStatusCB, hdr->hInternet, hdr, context, status, get_callback_name(status),
	  debugstr_status_info(status, new_info), info_len);
    
    hdr->lpfnStatusCB(hdr->hInternet, context, status, new_info, info_len);

    TRACE(" end callback().\n");

    if(new_info != info)
        heap_free(new_info);
}