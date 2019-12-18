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
struct tgl_dc {int flags; int auth_key_id; int* auth_key; TYPE_1__** options; } ;
struct TYPE_2__ {int port; int* ip; } ;

/* Variables and functions */
 int TGLDCF_LOGGED_IN ; 
 int /*<<< orphan*/  assert (int) ; 
 int strlen (int*) ; 
 int write (int,int*,int) ; 

void write_dc (struct tgl_dc *DC, void *extra) {
  int auth_file_fd = *(int *)extra;
  if (!DC) { 
    int x = 0;
    assert (write (auth_file_fd, &x, 4) == 4);
    return;
  } else {
    int x = 1;
    assert (write (auth_file_fd, &x, 4) == 4);
  }

  assert (DC->flags & TGLDCF_LOGGED_IN);

  assert (write (auth_file_fd, &DC->options[0]->port, 4) == 4);
  int l = strlen (DC->options[0]->ip);
  assert (write (auth_file_fd, &l, 4) == 4);
  assert (write (auth_file_fd, DC->options[0]->ip, l) == l);
  assert (write (auth_file_fd, &DC->auth_key_id, 8) == 8);
  assert (write (auth_file_fd, DC->auth_key, 256) == 256);
}