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
struct TYPE_7__ {scalar_t__ scheme_type; size_t host_len; char* host; scalar_t__ has_implicit_ip; } ;
typedef  TYPE_1__ parse_data ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_8__ {size_t host_start; size_t canon_len; char* canon_uri; size_t host_len; } ;
typedef  TYPE_2__ Uri ;
typedef  size_t DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRUE ; 
 scalar_t__ URL_SCHEME_UNKNOWN ; 
 scalar_t__ canonicalize_implicit_ipv4address (TYPE_1__ const*,TYPE_2__*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  debugstr_wn (char*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static BOOL canonicalize_ipv4address(const parse_data *data, Uri *uri, DWORD flags, BOOL computeOnly) {
    if(data->has_implicit_ip)
        return canonicalize_implicit_ipv4address(data, uri, flags, computeOnly);
    else {
        uri->host_start = uri->canon_len;

        /* Windows only normalizes for known scheme types. */
        if(data->scheme_type != URL_SCHEME_UNKNOWN) {
            /* parse_data contains a partial or full IPv4 address, so normalize it. */
            DWORD i, octetDigitCount = 0, octetCount = 0;
            BOOL octetHasDigit = FALSE;

            for(i = 0; i < data->host_len; ++i) {
                if(data->host[i] == '0' && !octetHasDigit) {
                    /* Can ignore leading zeros if:
                     *  1) It isn't the last digit of the octet.
                     *  2) i+1 != data->host_len
                     *  3) i+1 != '.'
                     */
                    if(octetDigitCount == 2 ||
                       i+1 == data->host_len ||
                       data->host[i+1] == '.') {
                        if(!computeOnly)
                            uri->canon_uri[uri->canon_len] = data->host[i];
                        ++uri->canon_len;
                        TRACE("Adding zero\n");
                    }
                } else if(data->host[i] == '.') {
                    if(!computeOnly)
                        uri->canon_uri[uri->canon_len] = data->host[i];
                    ++uri->canon_len;

                    octetDigitCount = 0;
                    octetHasDigit = FALSE;
                    ++octetCount;
                } else {
                    if(!computeOnly)
                        uri->canon_uri[uri->canon_len] = data->host[i];
                    ++uri->canon_len;

                    ++octetDigitCount;
                    octetHasDigit = TRUE;
                }
            }

            /* Make sure the canonicalized IP address has 4 dec-octets.
             * If doesn't add "0" ones until there is 4;
             */
            for( ; octetCount < 3; ++octetCount) {
                if(!computeOnly) {
                    uri->canon_uri[uri->canon_len] = '.';
                    uri->canon_uri[uri->canon_len+1] = '0';
                }

                uri->canon_len += 2;
            }
        } else {
            /* Windows doesn't normalize addresses in unknown schemes. */
            if(!computeOnly)
                memcpy(uri->canon_uri+uri->canon_len, data->host, data->host_len*sizeof(WCHAR));
            uri->canon_len += data->host_len;
        }

        uri->host_len = uri->canon_len - uri->host_start;
        if(!computeOnly)
            TRACE("(%p %p %x %d): Canonicalized IPv4 address, ip=%s len=%d\n",
                data, uri, flags, computeOnly,
                debugstr_wn(uri->canon_uri+uri->host_start, uri->host_len),
                uri->host_len);
    }

    return TRUE;
}