#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct timeval {int member_0; int /*<<< orphan*/  member_1; } ;
struct tgl_state {int /*<<< orphan*/  ev_base; } ;
struct tgl_message {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAX_UNREAD_MESSAGE_COUNT ; 
 struct tgl_state* TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  binlog_read ; 
 int /*<<< orphan*/  event_add (scalar_t__,struct timeval*) ; 
 int /*<<< orphan*/  event_free (scalar_t__) ; 
 scalar_t__ evtimer_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int log_level ; 
 int /*<<< orphan*/  memcpy (scalar_t__,struct tgl_message**,int) ; 
 int /*<<< orphan*/  print_read_list (int,scalar_t__) ; 
 int /*<<< orphan*/  unread_message_alarm ; 
 scalar_t__ unread_message_count ; 
 scalar_t__ unread_message_event ; 
 scalar_t__ unread_message_list ; 

void mark_read_upd (struct tgl_state *TLSR, int num, struct tgl_message *list[]) {
  assert (TLSR == TLS);
  if (!binlog_read) { return; }
  if (log_level < 1) { return; }

  if (unread_message_count + num <= MAX_UNREAD_MESSAGE_COUNT) {
    memcpy (unread_message_list + unread_message_count, list, num * sizeof (void *));
    unread_message_count += num;

    if (!unread_message_event) {
      unread_message_event = evtimer_new (TLS->ev_base, unread_message_alarm, 0);
      static struct timeval ptimeout = { 1, 0};
      event_add (unread_message_event, &ptimeout);
    }
  } else {
    print_read_list (unread_message_count, unread_message_list);
    print_read_list (num, list);
    unread_message_count = 0;
    if (unread_message_event) {
      event_free (unread_message_event);
      unread_message_event = 0;
    }
  }
}