#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ data; } ;
struct TYPE_7__ {TYPE_1__ session_data; } ;
struct TYPE_8__ {TYPE_2__ dnstls_data; } ;
typedef  TYPE_3__ DnsServer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int /*<<< orphan*/  gnutls_free (scalar_t__) ; 

void dnstls_server_free(DnsServer *server) {
        assert(server);

        if (server->dnstls_data.session_data.data)
                gnutls_free(server->dnstls_data.session_data.data);
}