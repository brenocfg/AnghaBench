#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ size; } ;
struct TYPE_13__ {scalar_t__ handshake; int shutdown; TYPE_4__* session; } ;
struct TYPE_14__ {TYPE_3__ dnstls_data; TYPE_2__* server; struct TYPE_14__* encrypted; } ;
struct TYPE_11__ {TYPE_6__ session_data; } ;
struct TYPE_12__ {TYPE_1__ dnstls_data; } ;
typedef  TYPE_4__ DnsStream ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int GNUTLS_E_AGAIN ; 
 scalar_t__ GNUTLS_E_SUCCESS ; 
 int /*<<< orphan*/  GNUTLS_SHUT_RDWR ; 
 scalar_t__ IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_4__*) ; 
 int /*<<< orphan*/  dns_stream_ref (TYPE_4__*) ; 
 int gnutls_bye (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_session_get_data2 (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  gnutls_strerror (int) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ) ; 

int dnstls_stream_shutdown(DnsStream *stream, int error) {
        int r;

        assert(stream);
        assert(stream->encrypted);
        assert(stream->dnstls_data.session);

        /* Store TLS Ticket for faster successive TLS handshakes */
        if (stream->server && stream->server->dnstls_data.session_data.size == 0 && stream->dnstls_data.handshake == GNUTLS_E_SUCCESS)
                gnutls_session_get_data2(stream->dnstls_data.session, &stream->server->dnstls_data.session_data);

        if (IN_SET(error, ETIMEDOUT, 0)) {
                r = gnutls_bye(stream->dnstls_data.session, GNUTLS_SHUT_RDWR);
                if (r == GNUTLS_E_AGAIN) {
                        if (!stream->dnstls_data.shutdown) {
                                stream->dnstls_data.shutdown = true;
                                dns_stream_ref(stream);
                                return -EAGAIN;
                        }
                } else if (r < 0)
                        log_debug("Failed to invoke gnutls_bye: %s", gnutls_strerror(r));
        }

        return 0;
}