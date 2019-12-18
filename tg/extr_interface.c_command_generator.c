#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tgl_peer_t ;
struct tgl_message {int /*<<< orphan*/  from_id; } ;
typedef  enum command_argument { ____Placeholder_command_argument } command_argument ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {unsigned int peer_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOT_FOUND ; 
 int /*<<< orphan*/  TGL_PEER_CHANNEL ; 
 int /*<<< orphan*/  TGL_PEER_CHAT ; 
 int /*<<< orphan*/  TGL_PEER_USER ; 
 int /*<<< orphan*/  TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__ autocomplete_id ; 
 TYPE_2__* autocomplete_peer ; 
#define  ca_channel 138 
#define  ca_chat 137 
#define  ca_command 136 
 int ca_double ; 
#define  ca_extf 135 
#define  ca_file_name 134 
#define  ca_file_name_end 133 
#define  ca_modifier 132 
 int ca_msg_id ; 
#define  ca_msg_string_end 131 
 int ca_none ; 
 int ca_number ; 
#define  ca_peer 130 
#define  ca_secret_chat 129 
 int ca_string ; 
 int ca_string_end ; 
#define  ca_user 128 
 int complete_chat_command (TYPE_2__*,int,char*,int,char**) ; 
 int complete_command_list (int,char*,int,char**) ; 
 int complete_spec_message_answer (struct tgl_message*,int,char*,int,char**) ; 
 int complete_string_list (int /*<<< orphan*/ ,int,char const*,int,char**) ; 
 int complete_user_command (TYPE_2__*,int,char*,int,char**) ; 
 int complete_username (int /*<<< orphan*/ ,int,char*,int,char**) ; 
 char* cur_token ; 
 int cur_token_len ; 
 int get_complete_mode () ; 
 int /*<<< orphan*/  in_chat_commands ; 
 scalar_t__ in_chat_mode ; 
 int /*<<< orphan*/  modifiers ; 
 char* rl_filename_completion_function (char*,int) ; 
 char* rl_line_buffer ; 
 size_t rl_point ; 
 int strlen (char const*) ; 
 int tgl_complete_channel_list (int /*<<< orphan*/ ,int,char*,int,char**) ; 
 int tgl_complete_chat_list (int /*<<< orphan*/ ,int,char*,int,char**) ; 
 int tgl_complete_encr_chat_list (int /*<<< orphan*/ ,int,char*,int,char**) ; 
 int tgl_complete_peer_list (int /*<<< orphan*/ ,int,char*,int,char**) ; 
 int tgl_complete_user_list (int /*<<< orphan*/ ,int,char*,int,char**) ; 
 int /*<<< orphan*/  tgl_get_peer_type (int /*<<< orphan*/ ) ; 
 struct tgl_message* tgl_message_get (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * tgl_peer_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tglf_extf_autocomplete (int /*<<< orphan*/ ,char const*,int,int,char**,char*,size_t) ; 

char *command_generator (const char *text, int state) {  
#ifndef DISABLE_EXTF
  static int len;
#endif
  static int index;
  static enum command_argument mode;
  static char *command_pos;
  static int command_len;

  if (in_chat_mode) {
    char *R = 0;
    index = complete_string_list (in_chat_commands, index, text, rl_point, &R);
    return R;
  }
 
  char c = 0;
  c = rl_line_buffer[rl_point];
  rl_line_buffer[rl_point] = 0;
  if (!state) {
#ifndef DISABLE_EXTF
    len = strlen (text);
#endif
    index = -1;
    
    mode = get_complete_mode ();
    command_pos = cur_token;
    command_len = cur_token_len;
  } else {
    if (mode != ca_file_name && mode != ca_file_name_end && index == -1) { return 0; }
  }
  
  if (mode == ca_none || mode == ca_string || mode == ca_string_end || mode == ca_number || mode == ca_double || mode == ca_msg_id) {   
    if (c) { rl_line_buffer[rl_point] = c; }
    return 0; 
  }
  assert (command_len >= 0);

  char *R = 0;
  switch (mode & 255) {
  case ca_command:
    index = complete_command_list (index, command_pos, command_len, &R);
    if (c) { rl_line_buffer[rl_point] = c; }
    return R;
  case ca_user:
    if (command_len && command_pos[0] == '@') {
      index = complete_username (TGL_PEER_USER, index, command_pos, command_len, &R);
    } else {
      index = tgl_complete_user_list (TLS, index, command_pos, command_len, &R);    
    }
    if (c) { rl_line_buffer[rl_point] = c; }
    return R;
  case ca_peer:
    if (command_len && command_pos[0] == '@') {
      index = complete_username (0, index, command_pos, command_len, &R);
    } else {
      index = tgl_complete_peer_list (TLS, index, command_pos, command_len, &R);
    }
    if (c) { rl_line_buffer[rl_point] = c; }
    return R;
  case ca_file_name:
  case ca_file_name_end:
    if (c) { rl_line_buffer[rl_point] = c; }
    R = rl_filename_completion_function (command_pos, state);
    return R;
  case ca_chat:
    index = tgl_complete_chat_list (TLS, index, command_pos, command_len, &R);
    if (c) { rl_line_buffer[rl_point] = c; }
    return R;
  case ca_secret_chat:
    index = tgl_complete_encr_chat_list (TLS, index, command_pos, command_len, &R);
    if (c) { rl_line_buffer[rl_point] = c; }
    return R;
  case ca_channel:
    if (command_len && command_pos[0] == '@') {
      index = complete_username (TGL_PEER_CHANNEL, index, command_pos, command_len, &R);
    } else {
      index = tgl_complete_channel_list (TLS, index, command_pos, command_len, &R);    
    }
    if (c) { rl_line_buffer[rl_point] = c; }
    return R;
  case ca_modifier:
    index = complete_string_list (modifiers, index, command_pos, command_len, &R);
    if (c) { rl_line_buffer[rl_point] = c; }
    return R;
  case ca_msg_string_end:
    if (autocomplete_peer) {
      if (tgl_get_peer_type (autocomplete_peer->id) == TGL_PEER_USER) {
        index = complete_user_command (autocomplete_peer, index, command_pos, command_len, &R);
      }
      if (tgl_get_peer_type (autocomplete_peer->id) == TGL_PEER_CHAT) {
        index = complete_chat_command (autocomplete_peer, index, command_pos, command_len, &R);
      }
    }
    if (autocomplete_id.peer_type != (unsigned)NOT_FOUND) {
      struct tgl_message *M = tgl_message_get (TLS, &autocomplete_id);
      if (M) {
        if (command_len > 0 && *command_pos == '/') {
          tgl_peer_t *P = tgl_peer_get (TLS, M->from_id);
          if (P) {
            index = complete_user_command (autocomplete_peer, index, command_pos, command_len, &R);
          }
        } else {
          index = complete_spec_message_answer (M, index, command_pos, command_len, &R);
        }
      }
    }
    if (c) { rl_line_buffer[rl_point] = c; }
    return R;
#ifndef DISABLE_EXTF
  case ca_extf:
    index = tglf_extf_autocomplete (TLS, text, len, index, &R, rl_line_buffer, rl_point);
    if (c) { rl_line_buffer[rl_point] = c; }
    return R;
#endif
  default:
    if (c) { rl_line_buffer[rl_point] = c; }
    return 0;
  }
}