#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_6__ {size_t idLength; int* ids; } ;
typedef  int BYTE ;
typedef  TYPE_1__ AsnObjectIdentifier ;
typedef  int /*<<< orphan*/  AsnInteger32 ;

/* Variables and functions */
 int /*<<< orphan*/  SNMP_ERRORSTATUS_NOERROR ; 
 int /*<<< orphan*/  SNMP_ERRORSTATUS_NOSUCHNAME ; 
#define  SNMP_PDU_GETNEXT 128 
 int /*<<< orphan*/  SnmpUtilOidNCmp (TYPE_1__*,TYPE_1__*,size_t) ; 

__attribute__((used)) static AsnInteger32 getItemAndIntegerInstanceFromOid(AsnObjectIdentifier *oid,
    AsnObjectIdentifier *base, BYTE bPduType, UINT *item, UINT *instance)
{
    AsnInteger32 ret = SNMP_ERRORSTATUS_NOERROR;

    switch (bPduType)
    {
    case SNMP_PDU_GETNEXT:
        if (SnmpUtilOidNCmp(oid, base, base->idLength) < 0)
        {
            *item = 1;
            *instance = 1;
        }
        else if (!SnmpUtilOidNCmp(oid, base, base->idLength))
        {
            if (oid->idLength == base->idLength ||
                oid->idLength == base->idLength + 1)
            {
                /* Either the table or an item within the table is specified,
                 * but the instance is not.  Get the first instance.
                 */
                *instance = 1;
                if (oid->idLength == base->idLength + 1)
                    *item = oid->ids[base->idLength];
                else
                    *item = 1;
            }
            else
            {
                *item = oid->ids[base->idLength];
                *instance = oid->ids[base->idLength + 1] + 1;
            }
        }
        else
            ret = SNMP_ERRORSTATUS_NOSUCHNAME;
        break;
    default:
        if (!SnmpUtilOidNCmp(oid, base, base->idLength))
        {
            if (oid->idLength == base->idLength ||
                oid->idLength == base->idLength + 1)
            {
                /* Either the table or an item within the table is specified,
                 * but the instance is not.
                 */
                ret = SNMP_ERRORSTATUS_NOSUCHNAME;
            }
            else
            {
                *item = oid->ids[base->idLength];
                *instance = oid->ids[base->idLength + 1];
            }
        }
        else
            ret = SNMP_ERRORSTATUS_NOSUCHNAME;
    }
    return ret;
}