#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * ids; } ;
struct TYPE_7__ {int /*<<< orphan*/ * stream; int /*<<< orphan*/  dynamic; } ;
struct TYPE_8__ {TYPE_1__ object; TYPE_2__ string; } ;
struct TYPE_9__ {int asnType; TYPE_3__ asnValue; } ;
typedef  TYPE_4__ AsnAny ;

/* Variables and functions */
#define  ASN_BITS 133 
#define  ASN_IPADDRESS 132 
 int ASN_NULL ; 
#define  ASN_OBJECTIDENTIFIER 131 
#define  ASN_OCTETSTRING 130 
#define  ASN_OPAQUE 129 
#define  ASN_SEQUENCE 128 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void asn_any_free(AsnAny *any)
{
    switch (any->asnType)
    {
    case ASN_OCTETSTRING:
    case ASN_BITS:
    case ASN_SEQUENCE:
    case ASN_IPADDRESS:
    case ASN_OPAQUE:
    {
        if (any->asnValue.string.dynamic)
        {
            HeapFree(GetProcessHeap(), 0, any->asnValue.string.stream);
            any->asnValue.string.stream = NULL;
        }
        break;
    }
    case ASN_OBJECTIDENTIFIER:
    {
        HeapFree(GetProcessHeap(), 0, any->asnValue.object.ids);
        any->asnValue.object.ids = NULL;
        break;
    }
    default: break;
    }
    any->asnType = ASN_NULL;
}