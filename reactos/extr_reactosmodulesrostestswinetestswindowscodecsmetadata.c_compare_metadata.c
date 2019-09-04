#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_12__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct test_data {scalar_t__ id; scalar_t__ type; scalar_t__ count; int* value; int /*<<< orphan*/  string; int /*<<< orphan*/  id_string; } ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_30__ {int /*<<< orphan*/  HighPart; int /*<<< orphan*/  LowPart; } ;
struct TYPE_29__ {scalar_t__ cbSize; int /*<<< orphan*/  pBlobData; } ;
struct TYPE_28__ {scalar_t__ cElems; int /*<<< orphan*/ * pElems; } ;
struct TYPE_27__ {scalar_t__ cElems; int* pElems; } ;
struct TYPE_26__ {scalar_t__ cElems; TYPE_4__* pElems; } ;
struct TYPE_24__ {int /*<<< orphan*/  HighPart; int /*<<< orphan*/  LowPart; } ;
struct TYPE_25__ {int QuadPart; TYPE_3__ u; } ;
struct TYPE_23__ {scalar_t__ cElems; int* pElems; } ;
struct TYPE_22__ {scalar_t__ cElems; int* pElems; } ;
struct TYPE_19__ {int QuadPart; TYPE_9__ u; } ;
struct TYPE_21__ {scalar_t__ uiVal; TYPE_10__ uhVal; TYPE_8__ blob; int /*<<< orphan*/  pszVal; TYPE_7__ calpstr; TYPE_6__ caub; TYPE_5__ cauh; TYPE_2__ caul; TYPE_1__ caui; int /*<<< orphan*/  pwszVal; } ;
struct TYPE_20__ {scalar_t__ vt; } ;
typedef  TYPE_11__ PROPVARIANT ;
typedef  int /*<<< orphan*/  IWICMetadataReader ;
typedef  int /*<<< orphan*/  IWICEnumMetadataItem ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ IWICEnumMetadataItem_Next (int /*<<< orphan*/ *,int,TYPE_11__*,TYPE_11__*,TYPE_11__*,int*) ; 
 int /*<<< orphan*/  IWICEnumMetadataItem_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IWICMetadataReader_GetEnumerator (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PropVariantClear (TYPE_11__*) ; 
 int /*<<< orphan*/  PropVariantInit (TYPE_11__*) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 TYPE_12__ U (TYPE_11__) ; 
 int const VT_BLOB ; 
 scalar_t__ VT_EMPTY ; 
#define  VT_I1 138 
#define  VT_I2 137 
#define  VT_I4 136 
#define  VT_I8 135 
#define  VT_LPSTR 134 
 scalar_t__ VT_LPWSTR ; 
#define  VT_R4 133 
#define  VT_R8 132 
#define  VT_UI1 131 
#define  VT_UI2 130 
#define  VT_UI4 129 
#define  VT_UI8 128 
 int VT_VECTOR ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrlenA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void compare_metadata(IWICMetadataReader *reader, const struct test_data *td, ULONG count)
{
    HRESULT hr;
    IWICEnumMetadataItem *enumerator;
    PROPVARIANT schema, id, value;
    ULONG items_returned, i;

    hr = IWICMetadataReader_GetEnumerator(reader, NULL);
    ok(hr == E_INVALIDARG, "GetEnumerator error %#x\n", hr);

    hr = IWICMetadataReader_GetEnumerator(reader, &enumerator);
    ok(hr == S_OK, "GetEnumerator error %#x\n", hr);

    PropVariantInit(&schema);
    PropVariantInit(&id);
    PropVariantInit(&value);

    for (i = 0; i < count; i++)
    {
        hr = IWICEnumMetadataItem_Next(enumerator, 1, &schema, &id, &value, &items_returned);
        ok(hr == S_OK, "Next error %#x\n", hr);
        ok(items_returned == 1, "unexpected item count %u\n", items_returned);

        ok(schema.vt == VT_EMPTY, "%u: unexpected vt: %u\n", i, schema.vt);
        ok(id.vt == VT_UI2 || id.vt == VT_LPWSTR || id.vt == VT_EMPTY, "%u: unexpected vt: %u\n", i, id.vt);
        if (id.vt == VT_UI2)
            ok(U(id).uiVal == td[i].id, "%u: expected id %#x, got %#x\n", i, td[i].id, U(id).uiVal);
        else if (id.vt == VT_LPWSTR)
            ok(!lstrcmpW(td[i].id_string, U(id).pwszVal),
               "%u: expected %s, got %s\n", i, wine_dbgstr_w(td[i].id_string), wine_dbgstr_w(U(id).pwszVal));

        ok(value.vt == td[i].type, "%u: expected vt %#x, got %#x\n", i, td[i].type, value.vt);
        if (value.vt & VT_VECTOR)
        {
            ULONG j;
            switch (value.vt & ~VT_VECTOR)
            {
            case VT_I1:
            case VT_UI1:
                ok(td[i].count == U(value).caub.cElems, "%u: expected cElems %d, got %d\n", i, td[i].count, U(value).caub.cElems);
                for (j = 0; j < U(value).caub.cElems; j++)
                    ok(td[i].value[j] == U(value).caub.pElems[j], "%u: expected value[%d] %#x/%#x, got %#x\n", i, j, (ULONG)td[i].value[j], (ULONG)(td[i].value[j] >> 32), U(value).caub.pElems[j]);
                break;
            case VT_I2:
            case VT_UI2:
                ok(td[i].count == U(value).caui.cElems, "%u: expected cElems %d, got %d\n", i, td[i].count, U(value).caui.cElems);
                for (j = 0; j < U(value).caui.cElems; j++)
                    ok(td[i].value[j] == U(value).caui.pElems[j], "%u: expected value[%d] %#x/%#x, got %#x\n", i, j, (ULONG)td[i].value[j], (ULONG)(td[i].value[j] >> 32), U(value).caui.pElems[j]);
                break;
            case VT_I4:
            case VT_UI4:
            case VT_R4:
                ok(td[i].count == U(value).caul.cElems, "%u: expected cElems %d, got %d\n", i, td[i].count, U(value).caul.cElems);
                for (j = 0; j < U(value).caul.cElems; j++)
                    ok(td[i].value[j] == U(value).caul.pElems[j], "%u: expected value[%d] %#x/%#x, got %#x\n", i, j, (ULONG)td[i].value[j], (ULONG)(td[i].value[j] >> 32), U(value).caul.pElems[j]);
                break;
            case VT_I8:
            case VT_UI8:
            case VT_R8:
                ok(td[i].count == U(value).cauh.cElems, "%u: expected cElems %d, got %d\n", i, td[i].count, U(value).cauh.cElems);
                for (j = 0; j < U(value).cauh.cElems; j++)
                    ok(td[i].value[j] == U(value).cauh.pElems[j].QuadPart, "%u: expected value[%d] %08x/%08x, got %08x/%08x\n", i, j, (ULONG)td[i].value[j], (ULONG)(td[i].value[j] >> 32), U(value).cauh.pElems[j].u.LowPart, U(value).cauh.pElems[j].u.HighPart);
                break;
            case VT_LPSTR:
                ok(td[i].count == U(value).calpstr.cElems, "%u: expected cElems %d, got %d\n", i, td[i].count, U(value).caub.cElems);
                for (j = 0; j < U(value).calpstr.cElems; j++)
                    trace("%u: %s\n", j, U(value).calpstr.pElems[j]);
                /* fall through to not handled message */
            default:
                ok(0, "%u: array of type %d is not handled\n", i, value.vt & ~VT_VECTOR);
                break;
            }
        }
        else if (value.vt == VT_LPSTR)
        {
            ok(td[i].count == strlen(U(value).pszVal) ||
               broken(td[i].count == strlen(U(value).pszVal) + 1), /* before Win7 */
               "%u: expected count %d, got %d\n", i, td[i].count, lstrlenA(U(value).pszVal));
            if (td[i].count == strlen(U(value).pszVal))
                ok(!strcmp(td[i].string, U(value).pszVal),
                   "%u: expected %s, got %s\n", i, td[i].string, U(value).pszVal);
        }
        else if (value.vt == VT_BLOB)
        {
            ok(td[i].count == U(value).blob.cbSize, "%u: expected count %d, got %d\n", i, td[i].count, U(value).blob.cbSize);
            ok(!memcmp(td[i].string, U(value).blob.pBlobData, td[i].count), "%u: expected %s, got %s\n", i, td[i].string, U(value).blob.pBlobData);
        }
        else
            ok(U(value).uhVal.QuadPart == td[i].value[0], "%u: expected value %#x/%#x got %#x/%#x\n",
               i, (UINT)td[i].value[0], (UINT)(td[i].value[0] >> 32), U(value).uhVal.u.LowPart, U(value).uhVal.u.HighPart);

        PropVariantClear(&schema);
        PropVariantClear(&id);
        PropVariantClear(&value);
    }

    hr = IWICEnumMetadataItem_Next(enumerator, 1, &schema, &id, &value, &items_returned);
    ok(hr == S_FALSE, "Next should fail\n");
    ok(items_returned == 0, "unexpected item count %u\n", items_returned);

    IWICEnumMetadataItem_Release(enumerator);
}