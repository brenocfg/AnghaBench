#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct WkstaTransportEnumData {scalar_t__ n_read; int prefmaxlen; int /*<<< orphan*/  ret; scalar_t__* pbuf; scalar_t__ n_adapt; } ;
typedef  int /*<<< orphan*/  WKSTA_TRANSPORT_INFO_0 ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  scalar_t__ UCHAR ;
struct TYPE_10__ {int /*<<< orphan*/  dwIndex; } ;
struct TYPE_9__ {int /*<<< orphan*/  ifIndex; } ;
struct TYPE_8__ {void* wkti0_transport_address; void* wkti0_transport_name; void* wkti0_wan_ish; scalar_t__ wkti0_number_of_vcs; scalar_t__ wkti0_quality_of_service; } ;
typedef  TYPE_1__* PWKSTA_TRANSPORT_INFO_0 ;
typedef  TYPE_2__ NetBIOSAdapterImpl ;
typedef  TYPE_3__ MIB_IFROW ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  void* LMSTR ;
typedef  int DWORD ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_MORE_DATA ; 
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 void* FALSE ; 
 int /*<<< orphan*/  GetIfEntry (TYPE_3__*) ; 
 int MAX_PREFERRED_LENGTH ; 
 int MAX_TRANSPORT_ADDR ; 
 int MAX_TRANSPORT_NAME ; 
 int /*<<< orphan*/  NERR_Success ; 
 int /*<<< orphan*/  NetApiBufferAllocate (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  TRANSPORT_NBT ; 
 void* TRUE ; 
 int /*<<< orphan*/  debugstr_w (void*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wprint_mac (void*,int,TYPE_3__*) ; 
 int /*<<< orphan*/  wprint_name (void*,int,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static BOOL WkstaEnumAdaptersCallback(UCHAR totalLANAs, UCHAR lanaIndex,
 ULONG transport, const NetBIOSAdapterImpl *data, void *closure)
{
    BOOL ret;
    struct WkstaTransportEnumData *enumData = closure;

    if (enumData && enumData->pbuf)
    {
        if (lanaIndex == 0)
        {
            DWORD toAllocate;

            enumData->n_adapt = totalLANAs;
            enumData->n_read = 0;

            toAllocate = totalLANAs * (sizeof(WKSTA_TRANSPORT_INFO_0)
             + MAX_TRANSPORT_NAME * sizeof(WCHAR) +
             MAX_TRANSPORT_ADDR * sizeof(WCHAR));
            if (enumData->prefmaxlen != MAX_PREFERRED_LENGTH)
                toAllocate = enumData->prefmaxlen;
            NetApiBufferAllocate(toAllocate, (LPVOID *)enumData->pbuf);
        }
        if (*(enumData->pbuf))
        {
            UCHAR spaceFor;

            if (enumData->prefmaxlen == MAX_PREFERRED_LENGTH)
                spaceFor = totalLANAs;
            else
                spaceFor = enumData->prefmaxlen /
                 (sizeof(WKSTA_TRANSPORT_INFO_0) + (MAX_TRANSPORT_NAME +
                 MAX_TRANSPORT_ADDR) * sizeof(WCHAR));
            if (enumData->n_read < spaceFor)
            {
                PWKSTA_TRANSPORT_INFO_0 ti;
                LMSTR transport_name, transport_addr;
                MIB_IFROW ifRow;

                ti = (PWKSTA_TRANSPORT_INFO_0)(*(enumData->pbuf) +
                 enumData->n_read * sizeof(WKSTA_TRANSPORT_INFO_0));
                transport_name = (LMSTR)(*(enumData->pbuf) +
                 totalLANAs * sizeof(WKSTA_TRANSPORT_INFO_0) +
                 enumData->n_read * MAX_TRANSPORT_NAME * sizeof(WCHAR));
                transport_addr = (LMSTR)(*(enumData->pbuf) +
                 totalLANAs * (sizeof(WKSTA_TRANSPORT_INFO_0) +
                 MAX_TRANSPORT_NAME * sizeof(WCHAR)) +
                 enumData->n_read * MAX_TRANSPORT_ADDR * sizeof(WCHAR));

                ifRow.dwIndex = data->ifIndex;
                GetIfEntry(&ifRow);
                ti->wkti0_quality_of_service = 0;
                ti->wkti0_number_of_vcs = 0;
                ti->wkti0_transport_name = transport_name;
                wprint_name(ti->wkti0_transport_name, MAX_TRANSPORT_NAME,
                 transport, &ifRow);
                ti->wkti0_transport_address = transport_addr;
                wprint_mac(ti->wkti0_transport_address, MAX_TRANSPORT_ADDR,
                 &ifRow);
                if (!memcmp(&transport, TRANSPORT_NBT, sizeof(ULONG)))
                    ti->wkti0_wan_ish = TRUE;
                else
                    ti->wkti0_wan_ish = FALSE;
                TRACE("%d of %d:ti at %p\n", lanaIndex, totalLANAs, ti);
                TRACE("transport_name at %p %s\n",
                 ti->wkti0_transport_name,
                 debugstr_w(ti->wkti0_transport_name));
                TRACE("transport_address at %p %s\n",
                 ti->wkti0_transport_address,
                 debugstr_w(ti->wkti0_transport_address));
                enumData->n_read++;
                enumData->ret = NERR_Success;
                ret = TRUE;
            }
            else
            {
                enumData->ret = ERROR_MORE_DATA;
                ret = FALSE;
            }
        }
        else
        {
            enumData->ret = ERROR_OUTOFMEMORY;
            ret = FALSE;
        }
    }
    else
        ret = FALSE;
    return ret;
}