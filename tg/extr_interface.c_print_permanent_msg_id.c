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

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

char *print_permanent_msg_id (tgl_message_id_t id) {
  static char buf[2 * sizeof (tgl_message_id_t) + 1];
  
  unsigned char *s = (void *)&id;
  int i;
  for (i = 0; i < (int)sizeof (tgl_message_id_t); i++) {
    sprintf (buf + 2 * i, "%02x", (unsigned)s[i]);
  }
  return buf;
}