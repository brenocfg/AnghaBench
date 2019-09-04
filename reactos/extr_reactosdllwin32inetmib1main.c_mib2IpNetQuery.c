#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_7__ {int /*<<< orphan*/  dwNumEntries; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ SnmpVarBind ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  AsnObjectIdentifier ;
typedef  int /*<<< orphan*/  AsnInteger32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_OID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEFINE_SIZEOF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  SNMP_ERRORSTATUS_NOSUCHNAME ; 
 int /*<<< orphan*/  SNMP_ERRORSTATUS_READONLY ; 
#define  SNMP_PDU_GET 130 
#define  SNMP_PDU_GETNEXT 129 
#define  SNMP_PDU_SET 128 
 int /*<<< orphan*/  SnmpUtilOidToA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getItemAndIntegerInstanceFromOid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* ipNetTable ; 
 int /*<<< orphan*/  mapStructEntryToValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  mib2IpNet ; 
 int /*<<< orphan*/  mib2IpNetMap ; 
 int /*<<< orphan*/  setOidWithItemAndInteger (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL mib2IpNetQuery(BYTE bPduType, SnmpVarBind *pVarBind,
    AsnInteger32 *pErrorStatus)
{
    AsnObjectIdentifier myOid = DEFINE_OID(mib2IpNet);
    BOOL ret = TRUE;

    TRACE("(0x%02x, %s, %p)\n", bPduType, SnmpUtilOidToA(&pVarBind->name),
        pErrorStatus);

    switch (bPduType)
    {
    case SNMP_PDU_GET:
    case SNMP_PDU_GETNEXT:
        if (!ipNetTable)
            *pErrorStatus = SNMP_ERRORSTATUS_NOSUCHNAME;
        else
        {
            UINT tableIndex = 0, item = 0;

            *pErrorStatus = getItemAndIntegerInstanceFromOid(&pVarBind->name,
                &myOid, bPduType, &item, &tableIndex);
            if (!*pErrorStatus)
            {
                assert(tableIndex);
                assert(item);
                if (tableIndex > ipNetTable->dwNumEntries)
                    *pErrorStatus = SNMP_ERRORSTATUS_NOSUCHNAME;
                else
                {
                    *pErrorStatus = mapStructEntryToValue(mib2IpNetMap,
                        DEFINE_SIZEOF(mib2IpNetMap),
                        &ipNetTable[tableIndex - 1], item, pVarBind);
                    if (!*pErrorStatus && bPduType == SNMP_PDU_GETNEXT)
                        ret = setOidWithItemAndInteger(&pVarBind->name, &myOid,
                            item, tableIndex);
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