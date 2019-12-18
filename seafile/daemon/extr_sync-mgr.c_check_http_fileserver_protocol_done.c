#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  version; int /*<<< orphan*/  not_supported; scalar_t__ check_success; } ;
struct TYPE_4__ {int /*<<< orphan*/  http_version; int /*<<< orphan*/  effective_host; int /*<<< orphan*/  use_fileserver_port; int /*<<< orphan*/  testing_host; int /*<<< orphan*/  checking; } ;
typedef  TYPE_1__ HttpServerState ;
typedef  TYPE_2__ HttpProtocolVersion ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_SYNC_PROTO_VERSION ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  http_fileserver_url (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_message (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_http_fileserver_protocol_done (HttpProtocolVersion *result, void *user_data)
{
    HttpServerState *state = user_data;

    state->checking = FALSE;

    if (result->check_success && !result->not_supported) {
        state->http_version = MIN(result->version, CURRENT_SYNC_PROTO_VERSION);
        state->effective_host = http_fileserver_url(state->testing_host);
        state->use_fileserver_port = TRUE;
        seaf_message ("File syncing protocol version on server %s is %d. "
                      "Client file syncing protocol version is %d. Use version %d.\n",
                      state->effective_host, result->version, CURRENT_SYNC_PROTO_VERSION,
                      state->http_version);
    }
}