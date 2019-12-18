#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  queries; } ;
struct TYPE_16__ {TYPE_2__* manager; int /*<<< orphan*/  request_address_string; TYPE_7__* request_dns_stream; int /*<<< orphan*/  reply_dns_packet; int /*<<< orphan*/  request_dns_packet; int /*<<< orphan*/  bus_track; int /*<<< orphan*/  request; int /*<<< orphan*/  question_utf8; int /*<<< orphan*/  question_idna; TYPE_1__* auxiliary_for; struct TYPE_16__* auxiliary_queries; } ;
struct TYPE_15__ {int /*<<< orphan*/  n_dns_queries; int /*<<< orphan*/  dns_queries; } ;
struct TYPE_14__ {scalar_t__ n_auxiliary_queries; int /*<<< orphan*/  auxiliary_queries; } ;
typedef  TYPE_3__ DnsQuery ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  auxiliary_queries ; 
 int /*<<< orphan*/  dns_packet_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_query_free_candidates (TYPE_3__*) ; 
 int /*<<< orphan*/  dns_query_reset_answer (TYPE_3__*) ; 
 int /*<<< orphan*/  dns_question_unref (int /*<<< orphan*/ ) ; 
 TYPE_7__* dns_stream_unref (TYPE_7__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_3__* mfree (TYPE_3__*) ; 
 int /*<<< orphan*/  queries ; 
 int /*<<< orphan*/  sd_bus_message_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_track_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_remove (int /*<<< orphan*/ ,TYPE_3__*) ; 

DnsQuery *dns_query_free(DnsQuery *q) {
        if (!q)
                return NULL;

        while (q->auxiliary_queries)
                dns_query_free(q->auxiliary_queries);

        if (q->auxiliary_for) {
                assert(q->auxiliary_for->n_auxiliary_queries > 0);
                q->auxiliary_for->n_auxiliary_queries--;
                LIST_REMOVE(auxiliary_queries, q->auxiliary_for->auxiliary_queries, q);
        }

        dns_query_free_candidates(q);

        dns_question_unref(q->question_idna);
        dns_question_unref(q->question_utf8);

        dns_query_reset_answer(q);

        sd_bus_message_unref(q->request);
        sd_bus_track_unref(q->bus_track);

        dns_packet_unref(q->request_dns_packet);
        dns_packet_unref(q->reply_dns_packet);

        if (q->request_dns_stream) {
                /* Detach the stream from our query, in case something else keeps a reference to it. */
                (void) set_remove(q->request_dns_stream->queries, q);
                q->request_dns_stream = dns_stream_unref(q->request_dns_stream);
        }

        free(q->request_address_string);

        if (q->manager) {
                LIST_REMOVE(queries, q->manager->dns_queries, q);
                q->manager->n_dns_queries--;
        }

        return mfree(q);
}