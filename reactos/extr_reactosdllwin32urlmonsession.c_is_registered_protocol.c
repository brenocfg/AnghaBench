#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoInternetParseUrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  PARSE_SCHEMA ; 
 scalar_t__ S_OK ; 
 scalar_t__ get_protocol_cf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BOOL is_registered_protocol(LPCWSTR url)
{
    DWORD schema_len;
    WCHAR schema[64];
    HRESULT hres;

    hres = CoInternetParseUrl(url, PARSE_SCHEMA, 0, schema, ARRAY_SIZE(schema), &schema_len, 0);
    if(FAILED(hres))
        return FALSE;

    return get_protocol_cf(schema, schema_len, NULL, NULL) == S_OK;
}