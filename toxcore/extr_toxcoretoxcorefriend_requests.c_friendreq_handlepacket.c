#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  message ;
struct TYPE_4__ {scalar_t__ handle_friendrequest_isset; scalar_t__ (* filter_function ) (scalar_t__ const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  handle_friendrequest_userdata; int /*<<< orphan*/  handle_friendrequest_object; int /*<<< orphan*/  (* handle_friendrequest ) (int /*<<< orphan*/ ,scalar_t__ const*,scalar_t__*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  filter_function_userdata; int /*<<< orphan*/  nospam; } ;
typedef  TYPE_1__ Friend_Requests ;

/* Variables and functions */
 int ONION_CLIENT_MAX_DATA_SIZE ; 
 int /*<<< orphan*/  addto_receivedlist (TYPE_1__*,scalar_t__ const*) ; 
 scalar_t__ memcmp (scalar_t__ const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,int) ; 
 scalar_t__ request_received (TYPE_1__*,scalar_t__ const*) ; 
 scalar_t__ stub1 (scalar_t__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__ const*,scalar_t__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int friendreq_handlepacket(void *object, const uint8_t *source_pubkey, const uint8_t *packet, uint16_t length)
{
    Friend_Requests *fr = object;

    if (length <= 1 + sizeof(fr->nospam) || length > ONION_CLIENT_MAX_DATA_SIZE)
        return 1;

    ++packet;
    --length;

    if (fr->handle_friendrequest_isset == 0)
        return 1;

    if (request_received(fr, source_pubkey))
        return 1;

    if (memcmp(packet, &fr->nospam, sizeof(fr->nospam)) != 0)
        return 1;

    if (fr->filter_function)
        if ((*fr->filter_function)(source_pubkey, fr->filter_function_userdata) != 0)
            return 1;

    addto_receivedlist(fr, source_pubkey);

    uint32_t message_len = length - sizeof(fr->nospam);
    uint8_t message[message_len + 1];
    memcpy(message, packet + sizeof(fr->nospam), message_len);
    message[sizeof(message) - 1] = 0; /* Be sure the message is null terminated. */

    (*fr->handle_friendrequest)(fr->handle_friendrequest_object, source_pubkey, message, message_len,
                                fr->handle_friendrequest_userdata);
    return 0;
}