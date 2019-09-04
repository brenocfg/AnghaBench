#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
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
 int /*<<< orphan*/  getItemFromOid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  icmpStats ; 
 int /*<<< orphan*/  mapStructEntryToValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  mib2Icmp ; 
 int /*<<< orphan*/  mib2IcmpMap ; 
 int /*<<< orphan*/  setOidWithItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL mib2IcmpQuery(BYTE bPduType, SnmpVarBind *pVarBind,
    AsnInteger32 *pErrorStatus)
{
    AsnObjectIdentifier myOid = DEFINE_OID(mib2Icmp);
    UINT item = 0;
    BOOL ret = TRUE;

    TRACE("(0x%02x, %s, %p)\n", bPduType, SnmpUtilOidToA(&pVarBind->name),
        pErrorStatus);

    switch (bPduType)
    {
    case SNMP_PDU_GET:
    case SNMP_PDU_GETNEXT:
        *pErrorStatus = getItemFromOid(&pVarBind->name, &myOid, bPduType,
            &item);
        if (!*pErrorStatus)
        {
            *pErrorStatus = mapStructEntryToValue(mib2IcmpMap,
                DEFINE_SIZEOF(mib2IcmpMap), &icmpStats, item,
                pVarBind);
            if (!*pErrorStatus && bPduType == SNMP_PDU_GETNEXT)
                ret = setOidWithItem(&pVarBind->name, &myOid, item);
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