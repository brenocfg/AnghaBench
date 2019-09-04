#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct GenericTable {int dummy; } ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_14__ {int /*<<< orphan*/  dwLocalPort; int /*<<< orphan*/  dwLocalAddr; } ;
struct TYPE_13__ {TYPE_6__* table; } ;
struct TYPE_12__ {int idLength; int /*<<< orphan*/ * ids; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ SnmpVarBind ;
typedef  int /*<<< orphan*/  MIB_UDPROW ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_2__ AsnObjectIdentifier ;
typedef  int /*<<< orphan*/  AsnInteger32 ;

/* Variables and functions */
 TYPE_2__ DEFINE_OID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEFINE_SIZEOF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  SNMP_ERRORSTATUS_NOSUCHNAME ; 
 int /*<<< orphan*/  SNMP_ERRORSTATUS_READONLY ; 
#define  SNMP_PDU_GET 130 
#define  SNMP_PDU_GETNEXT 129 
#define  SNMP_PDU_SET 128 
 int /*<<< orphan*/  SnmpUtilOidAppend (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  SnmpUtilOidToA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compareUdpRow ; 
 int /*<<< orphan*/  getItemAndInstanceFromTable (int /*<<< orphan*/ *,TYPE_2__*,int,int,struct GenericTable*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mapStructEntryToValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  mib2UdpEntry ; 
 int /*<<< orphan*/  mib2UdpEntryMap ; 
 int /*<<< orphan*/  oidToUdpRow ; 
 int /*<<< orphan*/  setOidWithItemAndIpAddr (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* udpTable ; 

__attribute__((used)) static BOOL mib2UdpEntryQuery(BYTE bPduType, SnmpVarBind *pVarBind,
    AsnInteger32 *pErrorStatus)
{
    AsnObjectIdentifier myOid = DEFINE_OID(mib2UdpEntry);
    BOOL ret = TRUE;

    TRACE("(0x%02x, %s, %p)\n", bPduType, SnmpUtilOidToA(&pVarBind->name),
        pErrorStatus);

    switch (bPduType)
    {
    case SNMP_PDU_GET:
    case SNMP_PDU_GETNEXT:
        if (!udpTable)
            *pErrorStatus = SNMP_ERRORSTATUS_NOSUCHNAME;
        else
        {
            UINT tableIndex = 0, item = 0;

            *pErrorStatus = getItemAndInstanceFromTable(&pVarBind->name, &myOid,
                5, bPduType, (struct GenericTable *)udpTable,
                sizeof(MIB_UDPROW), oidToUdpRow, compareUdpRow, &item,
                &tableIndex);
            if (!*pErrorStatus)
            {
                assert(tableIndex);
                assert(item);
                *pErrorStatus = mapStructEntryToValue(mib2UdpEntryMap,
                    DEFINE_SIZEOF(mib2UdpEntryMap),
                    &udpTable->table[tableIndex - 1], item, pVarBind);
                if (!*pErrorStatus && bPduType == SNMP_PDU_GETNEXT)
                {
                    AsnObjectIdentifier oid;

                    ret = setOidWithItemAndIpAddr(&pVarBind->name, &myOid, item,
                        udpTable->table[tableIndex - 1].dwLocalAddr);
                    if (ret)
                    {
                        oid.idLength = 1;
                        oid.ids = &udpTable->table[tableIndex - 1].dwLocalPort;
                        ret = SnmpUtilOidAppend(&pVarBind->name, &oid);
                    }
                }
            }
        }
        break;
    case SNMP_PDU_SET:
        *pErrorStatus = SNMP_ERRORSTATUS_READONLY;
        ret = FALSE;
        break;
    default:
        FIXME("0x%02x: unsupported PDU type\n", bPduType);
        *pErrorStatus = SNMP_ERRORSTATUS_NOSUCHNAME;
    }
    return ret;
}