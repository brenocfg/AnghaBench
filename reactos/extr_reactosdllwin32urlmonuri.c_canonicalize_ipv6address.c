#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ h16_count; scalar_t__ ipv4; } ;
struct TYPE_9__ {scalar_t__ scheme_type; int host_len; TYPE_3__ ipv6_address; int /*<<< orphan*/  host; } ;
typedef  TYPE_1__ parse_data ;
typedef  char WCHAR ;
struct TYPE_10__ {int host_start; int canon_len; char* canon_uri; int host_len; } ;
typedef  TYPE_2__ Uri ;
typedef  scalar_t__ USHORT ;
typedef  int UINT ;
typedef  int INT ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__ const*,TYPE_2__*,int,int,...) ; 
 int TRUE ; 
 scalar_t__ URL_SCHEME_UNKNOWN ; 
 int /*<<< orphan*/  compute_elision_location (TYPE_3__*,scalar_t__*,int*,int*) ; 
 int debugstr_wn (char*,int) ; 
 int /*<<< orphan*/  ipv6_to_number (TYPE_3__*,scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sprintfW (char*,char const*,scalar_t__) ; 
 int ui2ipv4 (char*,int) ; 

__attribute__((used)) static BOOL canonicalize_ipv6address(const parse_data *data, Uri *uri,
                                     DWORD flags, BOOL computeOnly) {
    uri->host_start = uri->canon_len;

    if(data->scheme_type == URL_SCHEME_UNKNOWN) {
        if(!computeOnly)
            memcpy(uri->canon_uri+uri->canon_len, data->host, data->host_len*sizeof(WCHAR));
        uri->canon_len += data->host_len;
    } else {
        USHORT values[8];
        INT elision_start;
        DWORD i, elision_len;

        if(!ipv6_to_number(&(data->ipv6_address), values)) {
            TRACE("(%p %p %x %d): Failed to compute numerical value for IPv6 address.\n",
                data, uri, flags, computeOnly);
            return FALSE;
        }

        if(!computeOnly)
            uri->canon_uri[uri->canon_len] = '[';
        ++uri->canon_len;

        /* Find where the elision should occur (if any). */
        compute_elision_location(&(data->ipv6_address), values, &elision_start, &elision_len);

        TRACE("%p %p %x %d): Elision starts at %d, len=%u\n", data, uri, flags,
            computeOnly, elision_start, elision_len);

        for(i = 0; i < 8; ++i) {
            BOOL in_elision = (elision_start > -1 && i >= elision_start &&
                               i < elision_start+elision_len);
            BOOL do_ipv4 = (i == 6 && data->ipv6_address.ipv4 && !in_elision &&
                            data->ipv6_address.h16_count == 0);

            if(i == elision_start) {
                if(!computeOnly) {
                    uri->canon_uri[uri->canon_len] = ':';
                    uri->canon_uri[uri->canon_len+1] = ':';
                }
                uri->canon_len += 2;
            }

            /* We can ignore the current component if we're in the elision. */
            if(in_elision)
                continue;

            /* We only add a ':' if we're not at i == 0, or when we're at
             * the very end of elision range since the ':' colon was handled
             * earlier. Otherwise we would end up with ":::" after elision.
             */
            if(i != 0 && !(elision_start > -1 && i == elision_start+elision_len)) {
                if(!computeOnly)
                    uri->canon_uri[uri->canon_len] = ':';
                ++uri->canon_len;
            }

            if(do_ipv4) {
                UINT val;
                DWORD len;

                /* Combine the two parts of the IPv4 address values. */
                val = values[i];
                val <<= 16;
                val += values[i+1];

                if(!computeOnly)
                    len = ui2ipv4(uri->canon_uri+uri->canon_len, val);
                else
                    len = ui2ipv4(NULL, val);

                uri->canon_len += len;
                ++i;
            } else {
                /* Write a regular h16 component to the URI. */

                /* Short circuit for the trivial case. */
                if(values[i] == 0) {
                    if(!computeOnly)
                        uri->canon_uri[uri->canon_len] = '0';
                    ++uri->canon_len;
                } else {
                    static const WCHAR formatW[] = {'%','x',0};

                    if(!computeOnly)
                        uri->canon_len += sprintfW(uri->canon_uri+uri->canon_len,
                                            formatW, values[i]);
                    else {
                        WCHAR tmp[5];
                        uri->canon_len += sprintfW(tmp, formatW, values[i]);
                    }
                }
            }
        }

        /* Add the closing ']'. */
        if(!computeOnly)
            uri->canon_uri[uri->canon_len] = ']';
        ++uri->canon_len;
    }

    uri->host_len = uri->canon_len - uri->host_start;

    if(!computeOnly)
        TRACE("(%p %p %x %d): Canonicalized IPv6 address %s, len=%d\n", data, uri, flags,
            computeOnly, debugstr_wn(uri->canon_uri+uri->host_start, uri->host_len),
            uri->host_len);

    return TRUE;
}