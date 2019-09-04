#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {scalar_t__ scheme_type; int is_opaque; int /*<<< orphan*/  has_port; int /*<<< orphan*/  host; int /*<<< orphan*/  password; int /*<<< orphan*/  username; int /*<<< orphan*/  is_relative; } ;
typedef  TYPE_2__ parse_data ;
struct TYPE_25__ {TYPE_1__* uri; scalar_t__ username; scalar_t__ password; } ;
typedef  TYPE_3__ UriBuilder ;
struct TYPE_23__ {int userinfo_split; int userinfo_start; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INET_E_INVALID_URL ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__ const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ URL_SCHEME_FILE ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setup_port (TYPE_3__ const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_fragment (TYPE_3__ const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_host (TYPE_3__ const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_path (TYPE_3__ const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_query (TYPE_3__ const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_scheme_name (TYPE_3__ const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_userinfo (TYPE_3__ const*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT validate_components(const UriBuilder *builder, parse_data *data, DWORD flags) {
    HRESULT hr;

    memset(data, 0, sizeof(parse_data));

    TRACE("(%p %p %x): Beginning to validate builder components.\n", builder, data, flags);

    hr = validate_scheme_name(builder, data, flags);
    if(FAILED(hr))
        return hr;

    /* Extra validation for file schemes. */
    if(data->scheme_type == URL_SCHEME_FILE) {
        if((builder->password || (builder->uri && builder->uri->userinfo_split > -1)) ||
           (builder->username || (builder->uri && builder->uri->userinfo_start > -1))) {
            TRACE("(%p %p %x): File schemes can't contain a username or password.\n",
                builder, data, flags);
            return INET_E_INVALID_URL;
        }
    }

    hr = validate_userinfo(builder, data, flags);
    if(FAILED(hr))
        return hr;

    hr = validate_host(builder, data, flags);
    if(FAILED(hr))
        return hr;

    setup_port(builder, data, flags);

    /* The URI is opaque if it doesn't have an authority component. */
    if(!data->is_relative)
        data->is_opaque = !data->username && !data->password && !data->host && !data->has_port
            && data->scheme_type != URL_SCHEME_FILE;
    else
        data->is_opaque = !data->host && !data->has_port;

    hr = validate_path(builder, data, flags);
    if(FAILED(hr))
        return hr;

    hr = validate_query(builder, data, flags);
    if(FAILED(hr))
        return hr;

    hr = validate_fragment(builder, data, flags);
    if(FAILED(hr))
        return hr;

    TRACE("(%p %p %x): Finished validating builder components.\n", builder, data, flags);

    return S_OK;
}