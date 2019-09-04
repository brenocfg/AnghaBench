#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t nCustHeaders; int /*<<< orphan*/  headers_section; TYPE_1__* custHeaders; } ;
typedef  TYPE_2__ http_request_t ;
struct TYPE_5__ {int wFlags; int /*<<< orphan*/  lpszValue; int /*<<< orphan*/  lpszField; } ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int HDR_ISREQUEST ; 
 int /*<<< orphan*/  HTTP_DeleteCustomHeader (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void HTTP_clear_response_headers( http_request_t *request )
{
    DWORD i;

    EnterCriticalSection( &request->headers_section );

    for( i=0; i<request->nCustHeaders; i++)
    {
        if( !request->custHeaders[i].lpszField )
            continue;
        if( !request->custHeaders[i].lpszValue )
            continue;
        if ( request->custHeaders[i].wFlags & HDR_ISREQUEST )
            continue;
        HTTP_DeleteCustomHeader( request, i );
        i--;
    }

    LeaveCriticalSection( &request->headers_section );
}