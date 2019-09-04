#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct string_t {char* str; int len; } ;
typedef  char WCHAR ;
typedef  int VARTYPE ;
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_9__ {char* bstrVal; int /*<<< orphan*/  puuid; } ;
struct TYPE_10__ {int vt; TYPE_1__ u; } ;
typedef  TYPE_2__ PROPVARIANT ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemAlloc (int) ; 
 scalar_t__ DISP_E_TYPEMISMATCH ; 
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ PropVariantChangeType (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PropVariantClear (TYPE_2__*) ; 
 int /*<<< orphan*/  PropVariantInit (TYPE_2__*) ; 
 scalar_t__ S_OK ; 
 void* SysAllocStringLen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,...) ; 
 scalar_t__ UuidFromStringW (char*,int /*<<< orphan*/ ) ; 
 void* VT_BSTR ; 
 int VT_CLSID ; 
 scalar_t__ VT_EMPTY ; 
 int VT_ILLEGAL ; 
 scalar_t__ WINCODEC_ERR_INVALIDQUERYREQUEST ; 
 scalar_t__ WINCODEC_ERR_WRONGSTATE ; 
 int map_type (struct string_t*) ; 
 char* memchrW (char const*,char,int) ; 
 int strtolW (char const*,char**,int) ; 
 int /*<<< orphan*/  wine_dbgstr_variant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wine_dbgstr_w (char*) ; 
 int /*<<< orphan*/  wine_dbgstr_wn (char*,int) ; 

__attribute__((used)) static HRESULT get_token(struct string_t *elem, PROPVARIANT *id, PROPVARIANT *schema, int *idx)
{
    const WCHAR *start, *end, *p;
    WCHAR *bstr;
    struct string_t next_elem;
    HRESULT hr;

    TRACE("%s, len %d\n", wine_dbgstr_wn(elem->str, elem->len), elem->len);

    PropVariantInit(id);
    PropVariantInit(schema);

    if (!elem->len) return S_OK;

    start = elem->str;

    if (*start == '[')
    {
        WCHAR *idx_end;

        if (start[1] < '0' || start[1] > '9') return DISP_E_TYPEMISMATCH;

        *idx = strtolW(start + 1, &idx_end, 10);
        if (idx_end > elem->str + elem->len) return WINCODEC_ERR_INVALIDQUERYREQUEST;
        if (*idx_end != ']') return WINCODEC_ERR_INVALIDQUERYREQUEST;
        if (*idx < 0) return WINCODEC_ERR_INVALIDQUERYREQUEST;
        end = idx_end + 1;

        next_elem.str = end;
        next_elem.len = elem->len - (end - start);
        hr = get_token(&next_elem, id, schema, idx);
        if (hr != S_OK)
        {
            TRACE("get_token error %#x\n", hr);
            return hr;
        }
        elem->len = (end - start) + next_elem.len;

        TRACE("indexed %s [%d]\n", wine_dbgstr_wn(elem->str, elem->len), *idx);
        return S_OK;
    }
    else if (*start == '{')
    {
        VARTYPE vt;
        PROPVARIANT next_token;

        end = memchrW(start + 1, '=', elem->len - 1);
        if (!end) return WINCODEC_ERR_INVALIDQUERYREQUEST;
        if (end > elem->str + elem->len) return WINCODEC_ERR_INVALIDQUERYREQUEST;

        next_elem.str = start + 1;
        next_elem.len = end - start - 1;
        vt = map_type(&next_elem);
        TRACE("type %s => %d\n", wine_dbgstr_wn(next_elem.str, next_elem.len), vt);
        if (vt == VT_ILLEGAL) return WINCODEC_ERR_WRONGSTATE;

        next_token.vt = VT_BSTR;
        next_token.u.bstrVal = SysAllocStringLen(NULL, elem->len - (end - start) + 1);
        if (!next_token.u.bstrVal) return E_OUTOFMEMORY;

        bstr = next_token.u.bstrVal;

        end++;
        p = end;
        while (*end && *end != '}' && end - start < elem->len)
        {
            if (*end == '\\') end++;
            *bstr++ = *end++;
        }
        if (*end != '}')
        {
            PropVariantClear(&next_token);
            return WINCODEC_ERR_INVALIDQUERYREQUEST;
        }
        *bstr = 0;
        TRACE("schema/id %s\n", wine_dbgstr_w(next_token.u.bstrVal));

        if (vt == VT_CLSID)
        {
            id->vt = VT_CLSID;
            id->u.puuid = CoTaskMemAlloc(sizeof(GUID));
            if (!id->u.puuid)
            {
                PropVariantClear(&next_token);
                return E_OUTOFMEMORY;
            }

            hr = UuidFromStringW(next_token.u.bstrVal, id->u.puuid);
        }
        else
            hr = PropVariantChangeType(id, &next_token, 0, vt);
        PropVariantClear(&next_token);
        if (hr != S_OK)
        {
            PropVariantClear(id);
            PropVariantClear(schema);
            return hr;
        }

        end++;
        if (*end == ':')
        {
            PROPVARIANT next_id, next_schema;
            int next_idx = 0;

            next_elem.str = end + 1;
            next_elem.len = elem->len - (end - start + 1);
            hr = get_token(&next_elem, &next_id, &next_schema, &next_idx);
            if (hr != S_OK)
            {
                TRACE("get_token error %#x\n", hr);
                return hr;
            }
            elem->len = (end - start + 1) + next_elem.len;

            TRACE("id %s [%d]\n", wine_dbgstr_wn(elem->str, elem->len), *idx);

            if (next_schema.vt != VT_EMPTY)
            {
                PropVariantClear(&next_id);
                PropVariantClear(&next_schema);
                return WINCODEC_ERR_WRONGSTATE;
            }

            *schema = *id;
            *id = next_id;

            return S_OK;
        }

        elem->len = end - start;
        return S_OK;
    }

    end = memchrW(start, '/', elem->len);
    if (!end) end = start + elem->len;

    p = memchrW(start, ':', end - start);
    if (p)
    {
        next_elem.str = p + 1;
        next_elem.len = end - p - 1;

        elem->len = p - start;
    }
    else
        elem->len = end - start;

    id->vt = VT_BSTR;
    id->u.bstrVal = SysAllocStringLen(NULL, elem->len + 1);
    if (!id->u.bstrVal) return E_OUTOFMEMORY;

    bstr = id->u.bstrVal;
    p = elem->str;
    while (p - elem->str < elem->len)
    {
        if (*p == '\\') p++;
        *bstr++ = *p++;
    }
    *bstr = 0;
    TRACE("%s [%d]\n", wine_dbgstr_variant((VARIANT *)id), *idx);

    if (*p == ':')
    {
        PROPVARIANT next_id, next_schema;
        int next_idx = 0;

        hr = get_token(&next_elem, &next_id, &next_schema, &next_idx);
        if (hr != S_OK)
        {
            TRACE("get_token error %#x\n", hr);
            PropVariantClear(id);
            PropVariantClear(schema);
            return hr;
        }
        elem->len += next_elem.len + 1;

        TRACE("id %s [%d]\n", wine_dbgstr_wn(elem->str, elem->len), *idx);

        if (next_schema.vt != VT_EMPTY)
        {
            PropVariantClear(&next_id);
            PropVariantClear(&next_schema);
            PropVariantClear(id);
            PropVariantClear(schema);
            return WINCODEC_ERR_WRONGSTATE;
        }

        *schema = *id;
        *id = next_id;
    }

    return S_OK;
}