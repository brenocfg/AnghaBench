#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct reader_position {int dummy; } ;
struct TYPE_9__ {struct reader_position position; } ;
typedef  TYPE_1__ xmlreader ;
typedef  int /*<<< orphan*/  strval ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WC_E_WHITESPACE ; 
 int /*<<< orphan*/  reader_add_attr (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct reader_position*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reader_cmp (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  reader_init_cstrvalue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_parse_pub_literal (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_parse_sys_literal (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_skipn (TYPE_1__*,int) ; 
 int reader_skipspaces (TYPE_1__*) ; 
 int /*<<< orphan*/  strlenW (char*) ; 

__attribute__((used)) static HRESULT reader_parse_externalid(xmlreader *reader)
{
    static WCHAR systemW[] = {'S','Y','S','T','E','M',0};
    static WCHAR publicW[] = {'P','U','B','L','I','C',0};
    struct reader_position position = reader->position;
    strval name, sys;
    HRESULT hr;
    int cnt;

    if (!reader_cmp(reader, publicW)) {
        strval pub;

        /* public id */
        reader_skipn(reader, 6);
        cnt = reader_skipspaces(reader);
        if (!cnt) return WC_E_WHITESPACE;

        hr = reader_parse_pub_literal(reader, &pub);
        if (FAILED(hr)) return hr;

        reader_init_cstrvalue(publicW, strlenW(publicW), &name);
        hr = reader_add_attr(reader, NULL, &name, NULL, &pub, &position, 0);
        if (FAILED(hr)) return hr;

        cnt = reader_skipspaces(reader);
        if (!cnt) return S_OK;

        /* optional system id */
        hr = reader_parse_sys_literal(reader, &sys);
        if (FAILED(hr)) return S_OK;

        reader_init_cstrvalue(systemW, strlenW(systemW), &name);
        hr = reader_add_attr(reader, NULL, &name, NULL, &sys, &position, 0);
        if (FAILED(hr)) return hr;

        return S_OK;
    } else if (!reader_cmp(reader, systemW)) {
        /* system id */
        reader_skipn(reader, 6);
        cnt = reader_skipspaces(reader);
        if (!cnt) return WC_E_WHITESPACE;

        hr = reader_parse_sys_literal(reader, &sys);
        if (FAILED(hr)) return hr;

        reader_init_cstrvalue(systemW, strlenW(systemW), &name);
        return reader_add_attr(reader, NULL, &name, NULL, &sys, &position, 0);
    }

    return S_FALSE;
}