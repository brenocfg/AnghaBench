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
typedef  TYPE_1__* lpCallbackData ;
typedef  int UINT ;
struct TYPE_3__ {char* szTrace2; char* szTrace1; int dwCounter1; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IDirectPlay4 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  DPID ;

/* Variables and functions */
 int /*<<< orphan*/  DPERR_NOMESSAGES ; 
 int /*<<< orphan*/  DP_OK ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirectPlayX_Receive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  checkHR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* dpid2char (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static void check_messages( IDirectPlay4 *pDP, DPID *dpid, DWORD dpidSize,
        lpCallbackData callbackData )
{
    /* Retrieves all messages from the queue of pDP, performing tests
     * to check if we are receiving what we expect.
     *
     * Information about the messages is stores in callbackData:
     *
     * callbackData->dwCounter1: Number of messages received.
     * callbackData->szTrace1: Traces for sender and receiver.
     *     We store the position a dpid holds in the dpid array.
     *     Example:
     *
     *       trace string: "01,02,03,14"
     *           expanded: [ '01', '02', '03', '14' ]
     *                         \     \     \     \
     *                          \     \     \     ) message 3: from 1 to 4
     *                           \     \     ) message 2: from 0 to 3
     *                            \     ) message 1: from 0 to 2
     *                             ) message 0: from 0 to 1
     *
     *     In general terms:
     *       sender of message i   = character in place 3*i of the array
     *       receiver of message i = character in place 3*i+1 of the array
     *
     *     A sender value of 'S' means DPID_SYSMSG, this is, a system message.
     *
     * callbackData->szTrace2: Traces for message sizes.
     */

    DPID idFrom, idTo;
    UINT i;
    DWORD dwDataSize = 1024;
    LPVOID lpData = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, dwDataSize );
    HRESULT hr;
    char temp[5];

    callbackData->szTrace2[0] = '\0';

    i = 0;
    while ( DP_OK == (hr = IDirectPlayX_Receive( pDP, &idFrom, &idTo, 0,
                                                 lpData, &dwDataSize )) )
    {

        callbackData->szTrace1[ 3*i   ] = dpid2char( dpid, dpidSize, idFrom );
        callbackData->szTrace1[ 3*i+1 ] = dpid2char( dpid, dpidSize, idTo );
        callbackData->szTrace1[ 3*i+2 ] = ',';

        sprintf( temp, "%d,", dwDataSize );
        strcat( callbackData->szTrace2, temp );

        dwDataSize = 1024;
        ++i;
    }

    checkHR( DPERR_NOMESSAGES, hr );

    callbackData->szTrace1[ 3*i ] = '\0';
    callbackData->dwCounter1 = i;


    HeapFree( GetProcessHeap(), 0, lpData );
}