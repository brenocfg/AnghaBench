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

/* Variables and functions */
 int O_CREAT ; 
 int O_RDWR ; 
 scalar_t__ STATE_FILE_MAGIC ; 
 int /*<<< orphan*/  TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ binlog_enabled ; 
 int /*<<< orphan*/  bl_do_set_date (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bl_do_set_pts (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bl_do_set_qts (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bl_do_set_seq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  get_state_filename () ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int read (int,int*,int) ; 

void read_state_file (void) {
  if (binlog_enabled) { return; }
  int state_file_fd = open (get_state_filename (), O_CREAT | O_RDWR, 0600);
  if (state_file_fd < 0) {
    return;
  }
  int version, magic;
  if (read (state_file_fd, &magic, 4) < 4) { close (state_file_fd); return; }
  if (magic != (int)STATE_FILE_MAGIC) { close (state_file_fd); return; }
  if (read (state_file_fd, &version, 4) < 4) { close (state_file_fd); return; }
  assert (version >= 0);
  int x[4];
  if (read (state_file_fd, x, 16) < 16) {
    close (state_file_fd); 
    return;
  }
  int pts = x[0];
  int qts = x[1];
  int seq = x[2];
  int date = x[3];
  close (state_file_fd); 
  bl_do_set_seq (TLS, seq);
  bl_do_set_pts (TLS, pts);
  bl_do_set_qts (TLS, qts);
  bl_do_set_date (TLS, date);
}