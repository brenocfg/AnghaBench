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
struct TYPE_7__ {scalar_t__ scheme_type; scalar_t__ host_len; char* host; } ;
typedef  TYPE_1__ parse_data ;
typedef  char WCHAR ;
struct TYPE_8__ {int host_start; size_t host_len; char* canon_uri; size_t canon_len; int authority_start; int /*<<< orphan*/  domain_offset; int /*<<< orphan*/  host_type; } ;
typedef  TYPE_2__ Uri ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  StrCmpNIW (char*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__ const*,TYPE_2__*,int,int,int /*<<< orphan*/ ,size_t) ; 
 int TRUE ; 
 scalar_t__ URL_SCHEME_FILE ; 
 scalar_t__ URL_SCHEME_UNKNOWN ; 
 int Uri_CREATE_FILE_USE_DOS_PATH ; 
 int Uri_CREATE_NO_CANONICALIZE ; 
 int Uri_CREATE_NO_ENCODE_FORBIDDEN_CHARACTERS ; 
 int /*<<< orphan*/  Uri_HOST_UNKNOWN ; 
 int /*<<< orphan*/  debugstr_wn (char*,size_t) ; 
 char decode_pct_val (char const*) ; 
 int /*<<< orphan*/  find_domain_name (char*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ is_ascii (char const) ; 
 int /*<<< orphan*/  is_reserved (char const) ; 
 scalar_t__ is_unreserved (char const) ; 
 scalar_t__ isupperW (char) ; 
 scalar_t__ lstrlenW (char const*) ; 
 int /*<<< orphan*/  pct_encode_val (char const,char*) ; 
 void* tolowerW (char const) ; 

__attribute__((used)) static BOOL canonicalize_reg_name(const parse_data *data, Uri *uri,
                                  DWORD flags, BOOL computeOnly) {
    static const WCHAR localhostW[] =
            {'l','o','c','a','l','h','o','s','t',0};
    const WCHAR *ptr;
    const BOOL known_scheme = data->scheme_type != URL_SCHEME_UNKNOWN;

    if(data->scheme_type == URL_SCHEME_FILE &&
       data->host_len == lstrlenW(localhostW)) {
        if(!StrCmpNIW(data->host, localhostW, data->host_len)) {
            uri->host_start = -1;
            uri->host_len = 0;
            uri->host_type = Uri_HOST_UNKNOWN;
            return TRUE;
        }
    }

    if(data->scheme_type == URL_SCHEME_FILE && flags & Uri_CREATE_FILE_USE_DOS_PATH) {
        if(!computeOnly) {
            uri->canon_uri[uri->canon_len] = '\\';
            uri->canon_uri[uri->canon_len+1] = '\\';
        }
        uri->canon_len += 2;
        uri->authority_start = uri->canon_len;
    }

    uri->host_start = uri->canon_len;

    for(ptr = data->host; ptr < data->host+data->host_len; ++ptr) {
        if(*ptr == '%' && known_scheme) {
            WCHAR val = decode_pct_val(ptr);
            if(is_unreserved(val)) {
                /* If NO_CANONICALIZE is not set, then windows lower cases the
                 * decoded value.
                 */
                if(!(flags & Uri_CREATE_NO_CANONICALIZE) && isupperW(val)) {
                    if(!computeOnly)
                        uri->canon_uri[uri->canon_len] = tolowerW(val);
                } else {
                    if(!computeOnly)
                        uri->canon_uri[uri->canon_len] = val;
                }
                ++uri->canon_len;

                /* Skip past the % encoded character. */
                ptr += 2;
                continue;
            } else {
                /* Just copy the % over. */
                if(!computeOnly)
                    uri->canon_uri[uri->canon_len] = *ptr;
                ++uri->canon_len;
            }
        } else if(*ptr == '\\') {
            /* Only unknown scheme types could have made it here with a '\\' in the host name. */
            if(!computeOnly)
                uri->canon_uri[uri->canon_len] = *ptr;
            ++uri->canon_len;
        } else if(!(flags & Uri_CREATE_NO_ENCODE_FORBIDDEN_CHARACTERS) && is_ascii(*ptr) &&
                  !is_unreserved(*ptr) && !is_reserved(*ptr) && known_scheme) {
            if(!computeOnly) {
                pct_encode_val(*ptr, uri->canon_uri+uri->canon_len);

                /* The percent encoded value gets lower cased also. */
                if(!(flags & Uri_CREATE_NO_CANONICALIZE)) {
                    uri->canon_uri[uri->canon_len+1] = tolowerW(uri->canon_uri[uri->canon_len+1]);
                    uri->canon_uri[uri->canon_len+2] = tolowerW(uri->canon_uri[uri->canon_len+2]);
                }
            }

            uri->canon_len += 3;
        } else {
            if(!computeOnly) {
                if(!(flags & Uri_CREATE_NO_CANONICALIZE) && known_scheme)
                    uri->canon_uri[uri->canon_len] = tolowerW(*ptr);
                else
                    uri->canon_uri[uri->canon_len] = *ptr;
            }

            ++uri->canon_len;
        }
    }

    uri->host_len = uri->canon_len - uri->host_start;

    if(!computeOnly)
        TRACE("(%p %p %x %d): Canonicalize reg_name=%s len=%d\n", data, uri, flags,
            computeOnly, debugstr_wn(uri->canon_uri+uri->host_start, uri->host_len),
            uri->host_len);

    if(!computeOnly)
        find_domain_name(uri->canon_uri+uri->host_start, uri->host_len,
            &(uri->domain_offset));

    return TRUE;
}