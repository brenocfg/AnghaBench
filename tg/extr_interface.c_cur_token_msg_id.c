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
 int /*<<< orphan*/  cur_token ; 
 int /*<<< orphan*/  cur_token_len ; 
 int /*<<< orphan*/  parse_input_msg_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tgl_message_id_t cur_token_msg_id (void) {
  return parse_input_msg_id (cur_token, cur_token_len);
}