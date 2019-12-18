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
typedef  int /*<<< orphan*/  tgl_message_id_t ;
struct tgl_message {int /*<<< orphan*/  temp_id; } ;
struct in_ev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mprintf (struct in_ev*,char*,...) ; 
 scalar_t__ msg_num_mode ; 
 int /*<<< orphan*/  permanent_msg_id_mode ; 
 int /*<<< orphan*/  print_permanent_msg_id (int /*<<< orphan*/ ) ; 

void print_msg_id (struct in_ev *ev, tgl_message_id_t msg_id, struct tgl_message *M) {
  if (msg_num_mode) {
    if (!permanent_msg_id_mode) {
      if (M) {
        mprintf (ev, "%d", M->temp_id);
      } else {
        mprintf (ev, "???");
      }
    } else {
      mprintf (ev, "%s", print_permanent_msg_id (msg_id));
    }
  }
}