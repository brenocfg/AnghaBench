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
 int SECRET_CHAT_FILE_MAGIC ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ binlog_enabled ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  get_secret_chat_filename () ; 
 int /*<<< orphan*/  lseek (int,int,int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tgl_peer_iterator_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int write (int,int*,int) ; 
 int /*<<< orphan*/  write_secret_chat ; 

void write_secret_chat_file (void) {
  if (binlog_enabled) { return; }
  int secret_chat_fd = open (get_secret_chat_filename (), O_CREAT | O_RDWR, 0600);
  assert (secret_chat_fd >= 0);
  int x = SECRET_CHAT_FILE_MAGIC;
  assert (write (secret_chat_fd, &x, 4) == 4);
  x = 2; 
  assert (write (secret_chat_fd, &x, 4) == 4); // version
  assert (write (secret_chat_fd, &x, 4) == 4); // num

  int y[2];
  y[0] = secret_chat_fd;
  y[1] = 0;

  tgl_peer_iterator_ex (TLS, write_secret_chat, y);

  lseek (secret_chat_fd, 8, SEEK_SET);
  assert (write (secret_chat_fd, &y[1], 4) == 4);
  close (secret_chat_fd);
}