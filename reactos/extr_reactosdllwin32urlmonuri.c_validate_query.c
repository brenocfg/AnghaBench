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
struct TYPE_10__ {int /*<<< orphan*/  query_len; int /*<<< orphan*/  const* query; } ;
typedef  TYPE_2__ parse_data ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_11__ {int modified_props; TYPE_1__* uri; int /*<<< orphan*/  query_len; int /*<<< orphan*/ * query; } ;
typedef  TYPE_3__ UriBuilder ;
struct TYPE_9__ {int query_start; int /*<<< orphan*/  query_len; int /*<<< orphan*/ * canon_uri; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  INET_E_INVALID_URL ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__ const*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int Uri_HAS_QUERY ; 
 int /*<<< orphan*/  debugstr_wn (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_query (int /*<<< orphan*/  const**,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT validate_query(const UriBuilder *builder, parse_data *data, DWORD flags) {
    const WCHAR *ptr = NULL;
    const WCHAR **pptr;
    DWORD expected_len;

    if(builder->query) {
        ptr = builder->query;
        expected_len = builder->query_len;
    } else if(!(builder->modified_props & Uri_HAS_QUERY) && builder->uri &&
              builder->uri->query_start > -1) {
        ptr = builder->uri->canon_uri+builder->uri->query_start;
        expected_len = builder->uri->query_len;
    }

    if(ptr) {
        const WCHAR *component = ptr;
        pptr = &ptr;

        if(parse_query(pptr, data, flags) && expected_len == data->query_len)
            TRACE("(%p %p %x): Valid query component %s len=%d.\n", builder, data, flags,
                debugstr_wn(data->query, data->query_len), data->query_len);
        else {
            TRACE("(%p %p %x): Invalid query component %s.\n", builder, data, flags,
                debugstr_wn(component, expected_len));
            return INET_E_INVALID_URL;
        }
    }

    return S_OK;
}