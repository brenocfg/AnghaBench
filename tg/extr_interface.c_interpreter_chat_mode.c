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
 int /*<<< orphan*/  TLS ; 
 int /*<<< orphan*/  chat_mode_id ; 
 scalar_t__ in_chat_mode ; 
 int /*<<< orphan*/  offline_mode ; 
 int /*<<< orphan*/  print_msg_list_gw ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  tgl_do_get_history (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tgl_do_mark_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tgl_do_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_prompt () ; 

void interpreter_chat_mode (char *line) {
  if (line == NULL || /* EOF received */
          !strncmp (line, "/exit", 5) || !strncmp (line, "/quit", 5)) {
    in_chat_mode = 0;
    update_prompt ();
    return;
  }
  if (!strncmp (line, "/history", 8)) {
    int limit = 40;
    sscanf (line, "/history %99d", &limit);
    if (limit < 0 || limit > 1000) { limit = 40; }
    tgl_do_get_history (TLS, chat_mode_id, 0, limit, offline_mode, print_msg_list_gw, 0);
    return;
  }
  if (!strncmp (line, "/read", 5)) {
    tgl_do_mark_read (TLS, chat_mode_id, 0, 0);
    return;
  }
  if (strlen (line) > 0) {
    tgl_do_send_message (TLS, chat_mode_id, line, strlen (line), 0, NULL, 0, 0);
  }
}