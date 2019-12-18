#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  errbuf ;
struct TYPE_14__ {int shutdown; TYPE_4__* ssl; } ;
struct TYPE_15__ {scalar_t__ dnstls_events; TYPE_3__ dnstls_data; TYPE_2__* server; struct TYPE_15__* encrypted; } ;
struct TYPE_12__ {int /*<<< orphan*/ * session; } ;
struct TYPE_13__ {TYPE_1__ dnstls_data; } ;
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  TYPE_4__ DnsStream ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ EPOLLIN ; 
 scalar_t__ EPOLLOUT ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  ERR_error_string_n (int,char*,int) ; 
 int ETIMEDOUT ; 
 scalar_t__ IN_SET (int,int,int /*<<< orphan*/ ) ; 
 int SSL_ERROR_SYSCALL ; 
 int SSL_ERROR_WANT_READ ; 
 int /*<<< orphan*/  SSL_ERROR_WANT_WRITE ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get1_session (TYPE_4__*) ; 
 int SSL_get_error (TYPE_4__*,int) ; 
 int SSL_shutdown (TYPE_4__*) ; 
 int /*<<< orphan*/  assert (TYPE_4__*) ; 
 int /*<<< orphan*/  dns_stream_ref (TYPE_4__*) ; 
 int dnstls_flush_write_buffer (TYPE_4__*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  log_debug (char*,char*) ; 
 int /*<<< orphan*/  log_debug_errno (scalar_t__,char*) ; 

int dnstls_stream_shutdown(DnsStream *stream, int error) {
        int ssl_error, r;
        SSL_SESSION *s;

        assert(stream);
        assert(stream->encrypted);
        assert(stream->dnstls_data.ssl);

        if (stream->server) {
                s = SSL_get1_session(stream->dnstls_data.ssl);
                if (s) {
                        if (stream->server->dnstls_data.session)
                                SSL_SESSION_free(stream->server->dnstls_data.session);

                        stream->server->dnstls_data.session = s;
                }
        }

        if (error == ETIMEDOUT) {
                ERR_clear_error();
                r = SSL_shutdown(stream->dnstls_data.ssl);
                if (r == 0) {
                        if (!stream->dnstls_data.shutdown) {
                                stream->dnstls_data.shutdown = true;
                                dns_stream_ref(stream);
                        }

                        stream->dnstls_events = 0;

                        r = dnstls_flush_write_buffer(stream);
                        if (r < 0)
                                return r;

                        return -EAGAIN;
                } else if (r < 0) {
                        ssl_error = SSL_get_error(stream->dnstls_data.ssl, r);
                        if (IN_SET(ssl_error, SSL_ERROR_WANT_READ, SSL_ERROR_WANT_WRITE)) {
                                stream->dnstls_events = ssl_error == SSL_ERROR_WANT_READ ? EPOLLIN : EPOLLOUT;
                                r = dnstls_flush_write_buffer(stream);
                                if (r < 0 && r != -EAGAIN)
                                        return r;

                                if (!stream->dnstls_data.shutdown) {
                                        stream->dnstls_data.shutdown = true;
                                        dns_stream_ref(stream);
                                }
                                return -EAGAIN;
                        } else if (ssl_error == SSL_ERROR_SYSCALL) {
                                if (errno > 0)
                                        log_debug_errno(errno, "Failed to invoke SSL_shutdown, ignoring: %m");
                        } else {
                                char errbuf[256];

                                ERR_error_string_n(ssl_error, errbuf, sizeof(errbuf));
                                log_debug("Failed to invoke SSL_shutdown, ignoring: %s", errbuf);
                        }
                }

                stream->dnstls_events = 0;
                r = dnstls_flush_write_buffer(stream);
                if (r < 0)
                        return r;
        }

        return 0;
}