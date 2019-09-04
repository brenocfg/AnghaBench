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
struct TYPE_3__ {int idLength; scalar_t__* ids; } ;
typedef  int DWORD ;
typedef  int BYTE ;
typedef  TYPE_1__ AsnObjectIdentifier ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD oidToIpAddr(AsnObjectIdentifier *oid)
{
    assert(oid && oid->idLength >= 4);
    /* Map the IDs to an IP address in little-endian order */
    return (BYTE)oid->ids[3] << 24 | (BYTE)oid->ids[2] << 16 |
        (BYTE)oid->ids[1] << 8 | (BYTE)oid->ids[0];
}