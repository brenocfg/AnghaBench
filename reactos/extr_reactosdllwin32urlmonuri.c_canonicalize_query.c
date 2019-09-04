#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ scheme_type; char* query; int query_len; } ;
typedef  TYPE_1__ parse_data ;
typedef  char WCHAR ;
struct TYPE_8__ {int query_start; size_t query_len; size_t canon_len; char* canon_uri; } ;
typedef  TYPE_2__ Uri ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,TYPE_1__ const*,TYPE_2__*,int,int,int /*<<< orphan*/ ,size_t) ; 
 int TRUE ; 
 scalar_t__ URL_SCHEME_UNKNOWN ; 
 int Uri_CREATE_NO_DECODE_EXTRA_INFO ; 
 int Uri_CREATE_NO_ENCODE_FORBIDDEN_CHARACTERS ; 
 int /*<<< orphan*/  debugstr_wn (char*,size_t) ; 
 char decode_pct_val (char const*) ; 
 scalar_t__ is_ascii (char const) ; 
 int /*<<< orphan*/  is_reserved (char const) ; 
 scalar_t__ is_unreserved (char const) ; 
 int /*<<< orphan*/  pct_encode_val (char const,char*) ; 

__attribute__((used)) static BOOL canonicalize_query(const parse_data *data, Uri *uri, DWORD flags, BOOL computeOnly) {
    const WCHAR *ptr, *end;
    const BOOL known_scheme = data->scheme_type != URL_SCHEME_UNKNOWN;

    if(!data->query) {
        uri->query_start = -1;
        uri->query_len = 0;
        return TRUE;
    }

    uri->query_start = uri->canon_len;

    end = data->query+data->query_len;
    for(ptr = data->query; ptr < end; ++ptr) {
        if(*ptr == '%') {
            if(known_scheme && !(flags & Uri_CREATE_NO_DECODE_EXTRA_INFO)) {
                WCHAR val = decode_pct_val(ptr);
                if(is_unreserved(val)) {
                    if(!computeOnly)
                        uri->canon_uri[uri->canon_len] = val;
                    ++uri->canon_len;

                    ptr += 2;
                    continue;
                }
            }
        } else if(known_scheme && is_ascii(*ptr) && !is_unreserved(*ptr) && !is_reserved(*ptr)) {
            if(!(flags & Uri_CREATE_NO_ENCODE_FORBIDDEN_CHARACTERS) &&
               !(flags & Uri_CREATE_NO_DECODE_EXTRA_INFO)) {
                if(!computeOnly)
                    pct_encode_val(*ptr, uri->canon_uri+uri->canon_len);
                uri->canon_len += 3;
                continue;
            }
        }

        if(!computeOnly)
            uri->canon_uri[uri->canon_len] = *ptr;
        ++uri->canon_len;
    }

    uri->query_len = uri->canon_len - uri->query_start;

    if(!computeOnly)
        TRACE("(%p %p %x %d): Canonicalized query string %s len=%d\n", data, uri, flags,
            computeOnly, debugstr_wn(uri->canon_uri+uri->query_start, uri->query_len),
            uri->query_len);
    return TRUE;
}