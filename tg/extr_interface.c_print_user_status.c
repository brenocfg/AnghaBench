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
struct tgl_user_status {int online; int /*<<< orphan*/  when; } ;
struct in_ev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  enable_json ; 
 int /*<<< orphan*/  mprintf (struct in_ev*,char*) ; 
 int /*<<< orphan*/  print_date_full (struct in_ev*,int /*<<< orphan*/ ) ; 

void print_user_status (struct tgl_user_status *S, struct in_ev *ev) {
  assert(!enable_json); //calling functions print_user_info_gw() and user_status_upd() already check.
  if (S->online > 0) {
    mprintf (ev, "online (was online ");
    print_date_full (ev, S->when);
    mprintf (ev, ")");
  } else {
    if (S->online == 0) {
      mprintf (ev, "offline");
    } else if (S->online == -1) {
      mprintf (ev, "offline (was online ");
      print_date_full (ev, S->when);
      mprintf (ev, ")");
    } else if (S->online == -2) {
      mprintf (ev, "offline (was online recently)");
    } else if (S->online == -3) {
      mprintf (ev, "offline (was online last week)");
    } else if (S->online == -4) {
      mprintf (ev, "offline (was online last month)");
    }
  }
}