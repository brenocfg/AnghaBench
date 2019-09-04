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
typedef  int /*<<< orphan*/  stringify_ctx_t ;
typedef  int WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ append_char (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  append_simple_quote (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  append_string (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  sprintfW (int*,int const*,int const) ; 

__attribute__((used)) static HRESULT json_quote(stringify_ctx_t *ctx, const WCHAR *ptr, size_t len)
{
    if(!ptr || !append_char(ctx, '"'))
        return E_OUTOFMEMORY;

    while(len--) {
        switch(*ptr) {
        case '"':
        case '\\':
            if(!append_simple_quote(ctx, *ptr))
                return E_OUTOFMEMORY;
            break;
        case '\b':
            if(!append_simple_quote(ctx, 'b'))
                return E_OUTOFMEMORY;
            break;
        case '\f':
            if(!append_simple_quote(ctx, 'f'))
                return E_OUTOFMEMORY;
            break;
        case '\n':
            if(!append_simple_quote(ctx, 'n'))
                return E_OUTOFMEMORY;
            break;
        case '\r':
            if(!append_simple_quote(ctx, 'r'))
                return E_OUTOFMEMORY;
            break;
        case '\t':
            if(!append_simple_quote(ctx, 't'))
                return E_OUTOFMEMORY;
            break;
        default:
            if(*ptr < ' ') {
                static const WCHAR formatW[] = {'\\','u','%','0','4','x',0};
                WCHAR buf[7];
                sprintfW(buf, formatW, *ptr);
                if(!append_string(ctx, buf))
                    return E_OUTOFMEMORY;
            }else {
                if(!append_char(ctx, *ptr))
                    return E_OUTOFMEMORY;
            }
        }
        ptr++;
    }

    return append_char(ctx, '"') ? S_OK : E_OUTOFMEMORY;
}