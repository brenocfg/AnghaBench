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
 int /*<<< orphan*/  O_RDWR ; 
 int SECRET_CHAT_FILE_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ binlog_enabled ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  get_secret_chat_filename () ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int read (int,int*,int) ; 
 int /*<<< orphan*/  read_secret_chat (int,int) ; 

void read_secret_chat_file (void) {
  if (binlog_enabled) { return; }
  int secret_chat_fd = open (get_secret_chat_filename (), O_RDWR, 0600);
  if (secret_chat_fd < 0) { return; }
  //assert (secret_chat_fd >= 0);
  int x;
  if (read (secret_chat_fd, &x, 4) < 4) { close (secret_chat_fd); return; }
  if (x != SECRET_CHAT_FILE_MAGIC) { close (secret_chat_fd); return; }
  int v = 0;
  assert (read (secret_chat_fd, &v, 4) == 4);
  assert (v == 0 || v == 1 || v == 2); // version  
  assert (read (secret_chat_fd, &x, 4) == 4);
  assert (x >= 0);
  while (x --> 0) {
    read_secret_chat (secret_chat_fd, v);
  }
  close (secret_chat_fd);
}