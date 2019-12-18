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
 int /*<<< orphan*/  AUTH_KEY_FILE ; 
 int /*<<< orphan*/  BINLOG_FILE ; 
 int /*<<< orphan*/  CONFIG_DIRECTORY ; 
 int /*<<< orphan*/  CONFIG_DIRECTORY_MODE ; 
 int /*<<< orphan*/  DOWNLOADS_DIRECTORY ; 
 int /*<<< orphan*/  SECRET_CHAT_FILE ; 
 int /*<<< orphan*/  STATE_FILE ; 
 int /*<<< orphan*/  TLS ; 
 char* auth_file_name ; 
 scalar_t__ binlog_enabled ; 
 char* binlog_file_name ; 
 int /*<<< orphan*/  disable_output ; 
 char* downloads_directory ; 
 int /*<<< orphan*/  get_home_directory () ; 
 int /*<<< orphan*/  mkdir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* secret_chat_file_name ; 
 char* state_file_name ; 
 int /*<<< orphan*/  tasprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tgl_set_binlog_mode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tgl_set_binlog_path (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tgl_set_download_directory (int /*<<< orphan*/ ,char*) ; 

void parse_config (void) {
  if (!disable_output) {
    printf ("libconfig not enabled\n");
  }
  tasprintf (&downloads_directory, "%s/%s/%s", get_home_directory (), CONFIG_DIRECTORY, DOWNLOADS_DIRECTORY);

  if (binlog_enabled) {
    tasprintf (&binlog_file_name, "%s/%s/%s", get_home_directory (), CONFIG_DIRECTORY, BINLOG_FILE);
    tgl_set_binlog_mode (TLS, 1);
    tgl_set_binlog_path (TLS, binlog_file_name);
  } else {
    tgl_set_binlog_mode (TLS, 0);
    //tgl_set_auth_file_path (auth_file_name;
    tasprintf (&auth_file_name, "%s/%s/%s", get_home_directory (), CONFIG_DIRECTORY, AUTH_KEY_FILE);
    tasprintf (&state_file_name, "%s/%s/%s", get_home_directory (), CONFIG_DIRECTORY, STATE_FILE);
    tasprintf (&secret_chat_file_name, "%s/%s/%s", get_home_directory (), CONFIG_DIRECTORY, SECRET_CHAT_FILE);
  }
  tgl_set_download_directory (TLS, downloads_directory);
  if (!mkdir (downloads_directory, CONFIG_DIRECTORY_MODE)) {
    if (!disable_output) {
      printf ("[%s] created\n", downloads_directory);
    }
  }
}