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

/* Variables and functions */
 int /*<<< orphan*/  TGL_PEER_CHAT ; 
 int /*<<< orphan*/  cur_token ; 
 int /*<<< orphan*/  cur_token_len ; 
 int /*<<< orphan*/  parse_input_peer_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tgl_peer_id_t cur_token_chat (void) {
  return parse_input_peer_id (cur_token, cur_token_len, TGL_PEER_CHAT);
}