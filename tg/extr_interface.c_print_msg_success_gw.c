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
struct tgl_state {int dummy; } ;
struct tgl_message {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_success_gw (struct tgl_state*,void*,int) ; 
 int /*<<< orphan*/  write_secret_chat_file () ; 

void print_msg_success_gw (struct tgl_state *TLS, void *extra, int success, struct tgl_message *M) {
  write_secret_chat_file ();
  print_success_gw (TLS, extra, success);
}