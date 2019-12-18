#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int peer_id; } ;
struct TYPE_5__ {int max_dc_num; int dc_working_num; TYPE_1__ our_id; } ;

/* Variables and functions */
 int DC_SERIALIZED_MAGIC ; 
 int O_CREAT ; 
 int O_RDWR ; 
 TYPE_2__* TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ binlog_enabled ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  get_auth_key_filename () ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tgl_dc_iterator_ex (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int write (int,int*,int) ; 
 int /*<<< orphan*/  write_dc ; 

void write_auth_file (void) {
  if (binlog_enabled) { return; }
  int auth_file_fd = open (get_auth_key_filename (), O_CREAT | O_RDWR, 0600);
  assert (auth_file_fd >= 0);
  int x = DC_SERIALIZED_MAGIC;
  assert (write (auth_file_fd, &x, 4) == 4);
  assert (write (auth_file_fd, &TLS->max_dc_num, 4) == 4);
  assert (write (auth_file_fd, &TLS->dc_working_num, 4) == 4);

  tgl_dc_iterator_ex (TLS, write_dc, &auth_file_fd);

  assert (write (auth_file_fd, &TLS->our_id.peer_id, 4) == 4);
  close (auth_file_fd);
}