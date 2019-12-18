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
typedef  scalar_t__ WORD ;
struct TYPE_3__ {int dwDataSize; scalar_t__* lpData; int /*<<< orphan*/  guidDataType; } ;
typedef  scalar_t__* LPVOID ;
typedef  scalar_t__ LPCSTR ;
typedef  int /*<<< orphan*/  IDirectPlayLobby3 ;
typedef  int /*<<< orphan*/  IDirectPlay4 ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ DPCOMPOUNDADDRESSELEMENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_ALL ; 
 int /*<<< orphan*/  CLSID_DirectPlayLobby ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__**) ; 
 int /*<<< orphan*/  DPAID_INet ; 
 int /*<<< orphan*/  DPAID_INetPort ; 
 int /*<<< orphan*/  DPAID_ServiceProvider ; 
 scalar_t__ DPERR_BUFFERTOOSMALL ; 
 int /*<<< orphan*/  DPSPGUID_TCPIP ; 
 scalar_t__ DP_OK ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ IDirectPlayLobby_CreateCompoundAddress (int /*<<< orphan*/ *,TYPE_1__*,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectPlayLobby_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IDirectPlayX_InitializeConnection (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IDirectPlayLobby3A ; 
 int /*<<< orphan*/  SUCCEEDED (scalar_t__) ; 
 int /*<<< orphan*/  checkHR (scalar_t__,scalar_t__) ; 
 int lstrlenA (scalar_t__) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void init_TCPIP_provider( IDirectPlay4 *pDP, LPCSTR strIPAddressString, WORD port )
{

    DPCOMPOUNDADDRESSELEMENT addressElements[3];
    LPVOID pAddress = NULL;
    DWORD dwAddressSize = 0;
    IDirectPlayLobby3 *pDPL;
    HRESULT hr;

    hr = CoCreateInstance( &CLSID_DirectPlayLobby, NULL, CLSCTX_ALL,
                           &IID_IDirectPlayLobby3A, (LPVOID*) &pDPL );
    ok (SUCCEEDED (hr), "CCI of CLSID_DirectPlayLobby / IID_IDirectPlayLobby3A failed\n");
    if (FAILED (hr)) return;

    /* Service provider */
    addressElements[0].guidDataType = DPAID_ServiceProvider;
    addressElements[0].dwDataSize   = sizeof(GUID);
    addressElements[0].lpData       = (LPVOID) &DPSPGUID_TCPIP;

    /* IP address string */
    addressElements[1].guidDataType = DPAID_INet;
    addressElements[1].dwDataSize   = lstrlenA(strIPAddressString) + 1;
    addressElements[1].lpData       = (LPVOID) strIPAddressString;

    /* Optional Port number */
    if( port > 0 )
    {
        addressElements[2].guidDataType = DPAID_INetPort;
        addressElements[2].dwDataSize   = sizeof(WORD);
        addressElements[2].lpData       = &port;
    }


    hr = IDirectPlayLobby_CreateCompoundAddress( pDPL, addressElements, 2,
                                                 NULL, &dwAddressSize );
    checkHR( DPERR_BUFFERTOOSMALL, hr );

    if( hr == DPERR_BUFFERTOOSMALL )
    {
        pAddress = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, dwAddressSize );
        hr = IDirectPlayLobby_CreateCompoundAddress( pDPL, addressElements, 2,
                                                     pAddress, &dwAddressSize );
        checkHR( DP_OK, hr );
    }

    hr = IDirectPlayX_InitializeConnection( pDP, pAddress, 0 );
    checkHR( DP_OK, hr );

    HeapFree( GetProcessHeap(), 0, pAddress );
    IDirectPlayLobby_Release(pDPL);
}