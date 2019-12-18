#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct RTPHeader {int pt; int /*<<< orphan*/  cpart; int /*<<< orphan*/  tlen; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  sequnum; } ;
struct TYPE_10__ {int sequnum; scalar_t__ timestamp; int tlen; } ;
struct TYPE_12__ {int len; scalar_t__ data; TYPE_1__ header; } ;
struct TYPE_11__ {int payload_type; int rsequnum; int (* mcb ) (int /*<<< orphan*/ ,TYPE_3__*) ;TYPE_3__* mp; int /*<<< orphan*/  bwc; scalar_t__ rtimestamp; int /*<<< orphan*/  cs; } ;
typedef  TYPE_2__ RTPSession ;
typedef  int /*<<< orphan*/  Messenger ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_WARNING (char*) ; 
 int MAX_CRYPTO_DATA_SIZE ; 
 int /*<<< orphan*/  bwc_add_lost (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bwc_add_recv (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bwc_feed_avg (int /*<<< orphan*/ ,int) ; 
 scalar_t__ chloss (TYPE_2__*,struct RTPHeader const*) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 TYPE_3__* new_message (int,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int stub2 (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int stub3 (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int stub4 (int /*<<< orphan*/ ,TYPE_3__*) ; 

int handle_rtp_packet (Messenger *m, uint32_t friendnumber, const uint8_t *data, uint16_t length, void *object)
{
    (void) m;
    (void) friendnumber;

    RTPSession *session = object;

    data ++;
    length--;

    if (!session || length < sizeof (struct RTPHeader)) {
        LOGGER_WARNING("No session or invalid length of received buffer!");
        return -1;
    }

    const struct RTPHeader *header = (struct RTPHeader *) data;

    if (header->pt != session->payload_type % 128) {
        LOGGER_WARNING("Invalid payload type with the session");
        return -1;
    }

    if (ntohs(header->cpart) >= ntohs(header->tlen)) {
        /* Never allow this case to happen */
        return -1;
    }

    bwc_feed_avg(session->bwc, length);

    if (ntohs(header->tlen) == length - sizeof (struct RTPHeader)) {
        /* The message is sent in single part */

        /* Only allow messages which have arrived in order;
         * drop late messages
         */
        if (chloss(session, header)) {
            return 0;
        } else {
            /* Message is not late; pick up the latest parameters */
            session->rsequnum = ntohs(header->sequnum);
            session->rtimestamp = ntohl(header->timestamp);
        }

        bwc_add_recv(session->bwc, length);

        /* Invoke processing of active multiparted message */
        if (session->mp) {
            if (session->mcb)
                session->mcb (session->cs, session->mp);
            else
                free(session->mp);

            session->mp = NULL;
        }

        /* The message came in the allowed time;
         * process it only if handler for the session is present.
         */

        if (!session->mcb)
            return 0;

        return session->mcb (session->cs, new_message(length, data, length));
    } else {
        /* The message is sent in multiple parts */

        if (session->mp) {
            /* There are 2 possible situations in this case:
             *      1) being that we got the part of already processing message.
             *      2) being that we got the part of a new/old message.
             *
             * We handle them differently as we only allow a single multiparted
             * processing message
             */

            if (session->mp->header.sequnum == ntohs(header->sequnum) &&
                    session->mp->header.timestamp == ntohl(header->timestamp)) {
                /* First case */

                /* Make sure we have enough allocated memory */
                if (session->mp->header.tlen - session->mp->len < length - sizeof(struct RTPHeader) ||
                        session->mp->header.tlen <= ntohs(header->cpart)) {
                    /* There happened to be some corruption on the stream;
                     * continue wihtout this part
                     */
                    return 0;
                }

                memcpy(session->mp->data + ntohs(header->cpart), data + sizeof(struct RTPHeader),
                       length - sizeof(struct RTPHeader));

                session->mp->len += length - sizeof(struct RTPHeader);

                bwc_add_recv(session->bwc, length);

                if (session->mp->len == session->mp->header.tlen) {
                    /* Received a full message; now push it for the further
                     * processing.
                     */
                    if (session->mcb)
                        session->mcb (session->cs, session->mp);
                    else
                        free(session->mp);

                    session->mp = NULL;
                }
            } else {
                /* Second case */

                if (session->mp->header.timestamp > ntohl(header->timestamp))
                    /* The received message part is from the old message;
                     * discard it.
                     */
                    return 0;

                /* Measure missing parts of the old message */
                bwc_add_lost(session->bwc,
                             (session->mp->header.tlen - session->mp->len) +

                             /* Must account sizes of rtp headers too */
                             ((session->mp->header.tlen - session->mp->len) /
                              MAX_CRYPTO_DATA_SIZE) * sizeof(struct RTPHeader) );

                /* Push the previous message for processing */
                if (session->mcb)
                    session->mcb (session->cs, session->mp);
                else
                    free(session->mp);

                session->mp = NULL;
                goto NEW_MULTIPARTED;
            }
        } else {
            /* In this case threat the message as if it was received in order
             */

            /* This is also a point for new multiparted messages */
NEW_MULTIPARTED:

            /* Only allow messages which have arrived in order;
             * drop late messages
             */
            if (chloss(session, header)) {
                return 0;
            } else {
                /* Message is not late; pick up the latest parameters */
                session->rsequnum = ntohs(header->sequnum);
                session->rtimestamp = ntohl(header->timestamp);
            }

            bwc_add_recv(session->bwc, length);

            /* Again, only store message if handler is present
             */
            if (session->mcb) {
                session->mp = new_message(ntohs(header->tlen) + sizeof(struct RTPHeader), data, length);

                /* Reposition data if necessary */
                if (ntohs(header->cpart));

                memmove(session->mp->data + ntohs(header->cpart), session->mp->data, session->mp->len);
            }
        }
    }

    return 0;
}