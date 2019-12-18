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
struct tgl_user {int /*<<< orphan*/  id; } ;
struct tgl_state {int dummy; } ;
struct tgl_chat {int /*<<< orphan*/  id; } ;
struct in_ev {int dummy; } ;
typedef  enum tgl_typing_status { ____Placeholder_tgl_typing_status } tgl_typing_status ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_YELLOW ; 
 struct tgl_state* TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ disable_output ; 
 scalar_t__ enable_json ; 
 int log_level ; 
 int /*<<< orphan*/  mpop_color (struct in_ev*) ; 
 int /*<<< orphan*/  mprint_end (struct in_ev*) ; 
 int /*<<< orphan*/  mprint_start (struct in_ev*) ; 
 int /*<<< orphan*/  mprintf (struct in_ev*,char*) ; 
 int /*<<< orphan*/  mpush_color (struct in_ev*,int /*<<< orphan*/ ) ; 
 struct in_ev* notify_ev ; 
 int /*<<< orphan*/  print_chat_name (struct in_ev*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  print_typing (struct in_ev*,int) ; 
 int /*<<< orphan*/  print_user_name (struct in_ev*,int /*<<< orphan*/ ,void*) ; 

void type_in_chat_notification_upd (struct tgl_state *TLSR, struct tgl_user *U, struct tgl_chat *C, enum tgl_typing_status status) {
  assert (TLSR == TLS);
  if (log_level < 2 || (disable_output && !notify_ev)) { return; }
  if (enable_json) { return; }
  struct in_ev *ev = notify_ev;
  mprint_start (ev);
  mpush_color (ev, COLOR_YELLOW);
  mprintf (ev, "User ");
  print_user_name (ev, U->id, (void *)U);
  mprintf (ev, " is ");
  print_typing (ev, status);
  mprintf (ev, " in chat ");
  print_chat_name (ev, C->id, (void *)C);
  mprintf (ev, "\n");
  mpop_color (ev);
  mprint_end (ev);
}