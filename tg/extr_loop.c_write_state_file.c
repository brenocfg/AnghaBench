#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int seq; int pts; int qts; int date; } ;

/* Variables and functions */
 int O_CREAT ; 
 int O_RDWR ; 
 int STATE_FILE_MAGIC ; 
 TYPE_1__* TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ binlog_enabled ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  do_halt (int) ; 
 int /*<<< orphan*/  get_state_filename () ; 
 int /*<<< orphan*/  logprintf (char*,int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int write (int,int*,int) ; 

void write_state_file (void) {
  if (binlog_enabled) { return; }
  static int wseq;
  static int wpts;
  static int wqts;
  static int wdate;
  if (wseq >= TLS->seq && wpts >= TLS->pts && wqts >= TLS->qts && wdate >= TLS->date) { return; }
  wseq = TLS->seq; wpts = TLS->pts; wqts = TLS->qts; wdate = TLS->date;
  int state_file_fd = open (get_state_filename (), O_CREAT | O_RDWR, 0600);
  if (state_file_fd < 0) {
    logprintf ("Can not write state file '%s': %m\n", get_state_filename ());
    do_halt (1);
  }
  int x[6];
  x[0] = STATE_FILE_MAGIC;
  x[1] = 0;
  x[2] = wpts;
  x[3] = wqts;
  x[4] = wseq;
  x[5] = wdate;
  assert (write (state_file_fd, x, 24) == 24);
  close (state_file_fd); 
}