#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  dwNumEntries; } ;
struct TYPE_9__ {int /*<<< orphan*/  idLength; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ SnmpVarBind ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_2__ AsnObjectIdentifier ;
typedef  int /*<<< orphan*/  AsnInteger32 ;

/* Variables and functions */
 TYPE_2__ DEFINE_OID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  SNMP_ERRORSTATUS_NOERROR ; 
 int /*<<< orphan*/  SNMP_ERRORSTATUS_NOSUCHNAME ; 
 int /*<<< orphan*/  SNMP_ERRORSTATUS_READONLY ; 
#define  SNMP_PDU_GET 130 
#define  SNMP_PDU_GETNEXT 129 
#define  SNMP_PDU_SET 128 
 int /*<<< orphan*/  SnmpUtilOidCpy (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  SnmpUtilOidFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SnmpUtilOidNCmp (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SnmpUtilOidToA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  copyInt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* ifTable ; 
 int /*<<< orphan*/  mib2IfNumber ; 

__attribute__((used)) static BOOL mib2IfNumberQuery(BYTE bPduType, SnmpVarBind *pVarBind,
    AsnInteger32 *pErrorStatus)
{
    AsnObjectIdentifier numberOid = DEFINE_OID(mib2IfNumber);
    BOOL ret = TRUE;

    TRACE("(0x%02x, %s, %p)\n", bPduType, SnmpUtilOidToA(&pVarBind->name),
        pErrorStatus);

    switch (bPduType)
    {
    case SNMP_PDU_GET:
    case SNMP_PDU_GETNEXT:
        if ((bPduType == SNMP_PDU_GET &&
            !SnmpUtilOidNCmp(&pVarBind->name, &numberOid, numberOid.idLength))
            || SnmpUtilOidNCmp(&pVarBind->name, &numberOid, numberOid.idLength)
            < 0)
        {
            DWORD numIfs = ifTable ? ifTable->dwNumEntries : 0;

            copyInt(&pVarBind->value, &numIfs);
            if (bPduType == SNMP_PDU_GETNEXT)
            {
                SnmpUtilOidFree(&pVarBind->name);
                SnmpUtilOidCpy(&pVarBind->name, &numberOid);
            }
            *pErrorStatus = SNMP_ERRORSTATUS_NOERROR;
        }
        else
        {
            *pErrorStatus = SNMP_ERRORSTATUS_NOSUCHNAME;
            /* Caller deals with OID if bPduType == SNMP_PDU_GETNEXT, so don't
             * need to set it here.
             */
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