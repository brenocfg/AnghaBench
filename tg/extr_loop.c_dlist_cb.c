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
typedef  int /*<<< orphan*/  tgl_peer_id_t ;
typedef  int /*<<< orphan*/  tgl_message_id_t ;
struct tgl_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLS ; 
 int /*<<< orphan*/  clist_cb ; 
 int /*<<< orphan*/  tgl_do_get_channels_dialog_list (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dlist_cb (struct tgl_state *TLSR, void *callback_extra, int success, int size, tgl_peer_id_t peers[], tgl_message_id_t *last_msg_id[], int unread_count[])  {
  tgl_do_get_channels_dialog_list (TLS, 100, 0, clist_cb, 0);
}