#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  bPhysAddr; int /*<<< orphan*/  dwPhysAddrLen; } ;
typedef  TYPE_1__* PMIB_IPNETROW ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  AsnAny ;

/* Variables and functions */
 int /*<<< orphan*/  ASN_OCTETSTRING ; 
 int FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIB_IPNETROW ; 
 int /*<<< orphan*/  SNMP_ERRORSTATUS_NOERROR ; 
 int /*<<< orphan*/  dwPhysAddrLen ; 
 int /*<<< orphan*/  setStringValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD copyIpNetPhysAddr(AsnAny *value, void *src)
{
    PMIB_IPNETROW row = (PMIB_IPNETROW)((BYTE *)src - FIELD_OFFSET(MIB_IPNETROW,
                                        dwPhysAddrLen));

    setStringValue(value, ASN_OCTETSTRING, row->dwPhysAddrLen, row->bPhysAddr);
    return SNMP_ERRORSTATUS_NOERROR;
}