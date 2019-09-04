#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_9__ {int idLength; size_t* ids; } ;
struct TYPE_8__ {size_t length; int /*<<< orphan*/  dynamic; int /*<<< orphan*/ * stream; } ;
struct TYPE_10__ {TYPE_2__ object; TYPE_1__ string; int /*<<< orphan*/  ticks; int /*<<< orphan*/  gauge; int /*<<< orphan*/  counter; int /*<<< orphan*/  counter64; int /*<<< orphan*/  unsigned32; int /*<<< orphan*/  number; } ;
struct TYPE_11__ {int asnType; TYPE_3__ asnValue; } ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  TYPE_4__ AsnAny ;

/* Variables and functions */
#define  ASN_BITS 139 
#define  ASN_COUNTER32 138 
#define  ASN_COUNTER64 137 
#define  ASN_GAUGE32 136 
#define  ASN_INTEGER32 135 
#define  ASN_IPADDRESS 134 
#define  ASN_OBJECTIDENTIFIER 133 
#define  ASN_OCTETSTRING 132 
#define  ASN_OPAQUE 131 
#define  ASN_SEQUENCE 130 
#define  ASN_TIMETICKS 129 
#define  ASN_UNSIGNED32 128 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  SNMPAPI_ERROR ; 
 int /*<<< orphan*/  SNMPAPI_NOERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static INT asn_any_copy(AsnAny *dst, const AsnAny *src)
{
    memset(dst, 0, sizeof(AsnAny));
    switch (src->asnType)
    {
    case ASN_INTEGER32:  dst->asnValue.number = src->asnValue.number; break;
    case ASN_UNSIGNED32: dst->asnValue.unsigned32 = src->asnValue.unsigned32; break;
    case ASN_COUNTER64:  dst->asnValue.counter64 = src->asnValue.counter64; break;
    case ASN_COUNTER32:  dst->asnValue.counter = src->asnValue.counter; break;
    case ASN_GAUGE32:    dst->asnValue.gauge = src->asnValue.gauge; break;
    case ASN_TIMETICKS:  dst->asnValue.ticks = src->asnValue.ticks; break;

    case ASN_OCTETSTRING:
    case ASN_BITS:
    case ASN_SEQUENCE:
    case ASN_IPADDRESS:
    case ASN_OPAQUE:
    {
        BYTE *stream;
        UINT length = src->asnValue.string.length;

        if (!(stream = HeapAlloc(GetProcessHeap(), 0, length))) return SNMPAPI_ERROR;
        memcpy(stream, src->asnValue.string.stream, length);

        dst->asnValue.string.stream = stream;
        dst->asnValue.string.length = length;
        dst->asnValue.string.dynamic = TRUE;
        break;
    }
    case ASN_OBJECTIDENTIFIER:
    {
        UINT *ids, i, size = src->asnValue.object.idLength * sizeof(UINT);

        if (!(ids = HeapAlloc(GetProcessHeap(), 0, size))) return SNMPAPI_ERROR;

        dst->asnValue.object.ids = ids;
        dst->asnValue.object.idLength = src->asnValue.object.idLength;

        for (i = 0; i < dst->asnValue.object.idLength; i++)
            dst->asnValue.object.ids[i] = src->asnValue.object.ids[i];
        break;
    }
    default:
    {
        WARN("unknown ASN type: %d\n", src->asnType);
        return SNMPAPI_ERROR;
    }
    }
    dst->asnType = src->asnType;
    return SNMPAPI_NOERROR;
}