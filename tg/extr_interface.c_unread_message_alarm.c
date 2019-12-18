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
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  event_free (scalar_t__) ; 
 int /*<<< orphan*/  print_read_list (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ unread_message_count ; 
 scalar_t__ unread_message_event ; 
 int /*<<< orphan*/  unread_message_list ; 

void unread_message_alarm (evutil_socket_t fd, short what, void *arg) {
  print_read_list (unread_message_count, unread_message_list);
  unread_message_count = 0;
  event_free (unread_message_event);
  unread_message_event = 0;
}