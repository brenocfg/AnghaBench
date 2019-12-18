#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int shutdown; int handshake; TYPE_2__* session; } ;
struct TYPE_10__ {void* dnstls_events; TYPE_1__ dnstls_data; struct TYPE_10__* encrypted; } ;
typedef  TYPE_2__ DnsStream ;

/* Variables and functions */
 int DNSTLS_STREAM_CLOSED ; 
 int EAGAIN ; 
 int ECONNREFUSED ; 
 void* EPOLLIN ; 
 void* EPOLLOUT ; 
 int GNUTLS_E_AGAIN ; 
 int /*<<< orphan*/  GNUTLS_SHUT_RDWR ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  dns_stream_unref (TYPE_2__*) ; 
 int gnutls_bye (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ gnutls_error_is_fatal (int) ; 
 int gnutls_handshake (TYPE_2__*) ; 
 int gnutls_record_get_direction (TYPE_2__*) ; 
 int /*<<< orphan*/  gnutls_strerror (int) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ) ; 

int dnstls_stream_on_io(DnsStream *stream, uint32_t revents) {
        int r;

        assert(stream);
        assert(stream->encrypted);
        assert(stream->dnstls_data.session);

        if (stream->dnstls_data.shutdown) {
                r = gnutls_bye(stream->dnstls_data.session, GNUTLS_SHUT_RDWR);
                if (r == GNUTLS_E_AGAIN) {
                        stream->dnstls_events = gnutls_record_get_direction(stream->dnstls_data.session) == 1 ? EPOLLOUT : EPOLLIN;
                        return -EAGAIN;
                } else if (r < 0)
                        log_debug("Failed to invoke gnutls_bye: %s", gnutls_strerror(r));

                stream->dnstls_events = 0;
                stream->dnstls_data.shutdown = false;
                dns_stream_unref(stream);
                return DNSTLS_STREAM_CLOSED;
        } else if (stream->dnstls_data.handshake < 0) {
                stream->dnstls_data.handshake = gnutls_handshake(stream->dnstls_data.session);
                if (stream->dnstls_data.handshake == GNUTLS_E_AGAIN) {
                        stream->dnstls_events = gnutls_record_get_direction(stream->dnstls_data.session) == 1 ? EPOLLOUT : EPOLLIN;
                        return -EAGAIN;
                } else if (stream->dnstls_data.handshake < 0) {
                        log_debug("Failed to invoke gnutls_handshake: %s", gnutls_strerror(stream->dnstls_data.handshake));
                        if (gnutls_error_is_fatal(stream->dnstls_data.handshake))
                                return -ECONNREFUSED;
                }

                stream->dnstls_events = 0;
        }

        return 0;
}