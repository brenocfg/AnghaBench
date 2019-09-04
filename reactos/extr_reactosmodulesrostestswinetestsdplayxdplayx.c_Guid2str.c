#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  char* LPCSTR ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  DPAID_ComPort ; 
 int /*<<< orphan*/  DPAID_INet ; 
 int /*<<< orphan*/  DPAID_INetPort ; 
 int /*<<< orphan*/  DPAID_INetW ; 
 int /*<<< orphan*/  DPAID_LobbyProvider ; 
 int /*<<< orphan*/  DPAID_Modem ; 
 int /*<<< orphan*/  DPAID_ModemW ; 
 int /*<<< orphan*/  DPAID_Phone ; 
 int /*<<< orphan*/  DPAID_PhoneW ; 
 int /*<<< orphan*/  DPAID_ServiceProvider ; 
 int /*<<< orphan*/  DPAID_TotalSize ; 
 int /*<<< orphan*/  DPSPGUID_IPX ; 
 int /*<<< orphan*/  DPSPGUID_MODEM ; 
 int /*<<< orphan*/  DPSPGUID_SERIAL ; 
 int /*<<< orphan*/  DPSPGUID_TCPIP ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 char* wine_dbgstr_guid (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static LPCSTR Guid2str(const GUID *guid)
{
    if (!guid) return "(null)";

    /* Service providers */
    if (IsEqualGUID(guid, &DPSPGUID_IPX))
        return "DPSPGUID_IPX";
    if (IsEqualGUID(guid, &DPSPGUID_TCPIP))
        return "DPSPGUID_TCPIP";
    if (IsEqualGUID(guid, &DPSPGUID_SERIAL))
        return "DPSPGUID_SERIAL";
    if (IsEqualGUID(guid, &DPSPGUID_MODEM))
        return "DPSPGUID_MODEM";
    /* DirectPlay Address IDs */
    if (IsEqualGUID(guid, &DPAID_TotalSize))
        return "DPAID_TotalSize";
    if (IsEqualGUID(guid, &DPAID_ServiceProvider))
        return "DPAID_ServiceProvider";
    if (IsEqualGUID(guid, &DPAID_LobbyProvider))
        return "DPAID_LobbyProvider";
    if (IsEqualGUID(guid, &DPAID_Phone))
        return "DPAID_Phone";
    if (IsEqualGUID(guid, &DPAID_PhoneW))
        return "DPAID_PhoneW";
    if (IsEqualGUID(guid, &DPAID_Modem))
        return "DPAID_Modem";
    if (IsEqualGUID(guid, &DPAID_ModemW))
        return "DPAID_ModemW";
    if (IsEqualGUID(guid, &DPAID_INet))
        return "DPAID_INet";
    if (IsEqualGUID(guid, &DPAID_INetW))
        return "DPAID_INetW";
    if (IsEqualGUID(guid, &DPAID_INetPort))
        return "DPAID_INetPort";
    if (IsEqualGUID(guid, &DPAID_ComPort))
        return "DPAID_ComPort";

    return wine_dbgstr_guid(guid);
}