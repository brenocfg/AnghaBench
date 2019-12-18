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
struct tgl_channel {int /*<<< orphan*/  username; } ;

/* Variables and functions */
 struct tgl_state* TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  binlog_read ; 
 scalar_t__ disable_output ; 
 int /*<<< orphan*/  notify_ev ; 
 int /*<<< orphan*/  peer_update_username (void*,int /*<<< orphan*/ ) ; 

void channel_update_gw (struct tgl_state *TLSR, struct tgl_channel *U, unsigned flags) {
  assert (TLSR == TLS);
  
  peer_update_username ((void *)U, U->username);
 
  if (disable_output && !notify_ev) { return; }
  if (!binlog_read) { return; }
}