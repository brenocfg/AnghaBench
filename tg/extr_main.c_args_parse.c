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
struct option {char* member_0; int member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  const member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLS ; 
 int accept_any_tcp ; 
 int alert_sound ; 
 int allow_weak_random ; 
 int /*<<< orphan*/  assert (int) ; 
 void* atoi (void*) ; 
 int binlog_enabled ; 
 void* bot_hash ; 
 int /*<<< orphan*/  bot_mode ; 
 int /*<<< orphan*/  config_filename ; 
 int /*<<< orphan*/  daemonize ; 
 int disable_auto_accept ; 
 int /*<<< orphan*/  disable_colors ; 
 int disable_link_preview ; 
 int /*<<< orphan*/  disable_output ; 
 int enable_json ; 
 int getopt_long (int,char**,char*,struct option*,int /*<<< orphan*/ *) ; 
 int ipv6_enabled ; 
 void* log_level ; 
 void* logname ; 
 void* lua_file ; 
 int /*<<< orphan*/  msg_num_mode ; 
#define  no_argument 130 
 void* optarg ; 
#define  optional_argument 129 
 int permanent_msg_id_mode ; 
 int permanent_peer_id_mode ; 
 void* port ; 
 void* prefix ; 
 void* python_file ; 
 int /*<<< orphan*/  readline_disabled ; 
#define  required_argument 128 
 int /*<<< orphan*/  reset_authorization ; 
 int /*<<< orphan*/  set_default_username (void*) ; 
 void* set_group_name ; 
 void* set_user_name ; 
 void* start_command ; 
 void* strdup (void*) ; 
 int strlen (void*) ; 
 int sync_from_start ; 
 int /*<<< orphan*/ * tgl_allocator ; 
 int /*<<< orphan*/  tgl_allocator_debug ; 
 int /*<<< orphan*/  tgl_incr_verbosity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tgl_set_rsa_key (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  tgl_state_alloc () ; 
 int /*<<< orphan*/  tstrdup (void*) ; 
 void* unix_socket ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  use_ids ; 
 int /*<<< orphan*/  verbosity ; 
 int wait_dialog_list ; 

void args_parse (int argc, char **argv) {
  TLS = tgl_state_alloc ();

  static struct option long_options[] = {
    {"debug-allocator", no_argument, 0,  1000 },
    {"phone", required_argument, 0, 'u'}, 
    {"rsa-key", required_argument, 0, 'k'},
    {"verbosity", no_argument, 0, 'v'},
    {"enable-msg-id", no_argument, 0, 'N'},
#ifdef HAVE_LIBCONFIG
    {"config", required_argument, 0, 'c'},
    {"profile", required_argument, 0, 'p'},
#else
    #if 0
    {"enable-binlog", no_argument, 0, 'B'},
    #endif
#endif
    {"log-level", required_argument, 0, 'l'},
    {"sync-from-start", no_argument, 0, 'f'},
    {"disable-auto-accept", no_argument, 0, 'E'},
    {"allow-weak-random", no_argument, 0, 'w'},
#ifdef USE_LUA
    {"lua-script", required_argument, 0, 's'},
#endif
    {"wait-dialog-list", no_argument, 0, 'W'},
    {"disable-colors", no_argument, 0, 'C'},
    {"disable-readline", no_argument, 0, 'R'},
    {"alert", no_argument, 0, 'A'},
    {"daemonize", no_argument, 0, 'd'},
    {"logname", required_argument, 0, 'L'},
    {"username", required_argument, 0, 'U'},
    {"groupname", required_argument, 0, 'G'},
    {"disable-output", no_argument, 0, 'D'},
    {"reset-authorization", no_argument, 0, 'q'},
    {"tcp-port", required_argument, 0, 'P'},
    {"unix-socket", required_argument, 0, 'S'},
    {"exec", required_argument, 0, 'e'},
    {"disable-names", no_argument, 0, 'I'},
    {"enable-ipv6", no_argument, 0, '6'},
    {"bot", optional_argument, 0, 'b'},
    {"help", no_argument, 0, 'h'},
    {"accept-any-tcp", no_argument, 0,  1001},
    {"disable-link-preview", no_argument, 0, 1002},
    {"json", no_argument, 0, 1003},
    {"python-script", required_argument, 0, 'Z'},
    {"permanent-msg-ids", no_argument, 0, 1004},
    {"permanent-peer-ids", no_argument, 0, 1005},
    {0,         0,                 0,  0 }
  };



  int opt = 0;
  while ((opt = getopt_long (argc, argv, "u:hk:vNl:fEwWCRAdL:DU:G:qP:S:e:I6b"
#ifdef HAVE_LIBCONFIG
  "c:p:"
#else
  #if 0
  "B"
  #endif
#endif
#ifdef USE_LUA
  "s:"
#endif
#ifdef USE_PYTHON
  "Z:"
#endif
  , long_options, NULL
  
  )) != -1) {
    switch (opt) {
    case 'b':
      bot_mode ++;
      if (optarg) {
        bot_hash = optarg;
      }
      break;
    case 1000:
      tgl_allocator = &tgl_allocator_debug;
      break;
    case 1001:
      accept_any_tcp = 1;
      break;
    case 'u':
      set_default_username (optarg);
      break;
    case 'k':
      //rsa_public_key_name = tstrdup (optarg);
      tgl_set_rsa_key (TLS, optarg);
      break;
    case 'v':
      tgl_incr_verbosity (TLS);
      verbosity ++;
      break;
    case 'N':
      msg_num_mode ++;
      break;
#ifdef HAVE_LIBCONFIG
    case 'c':
      config_filename = tstrdup (optarg);
      break;
    case 'p':
      prefix = optarg;
      assert (strlen (prefix) <= 100);
      break;
#else
    #if 0
    case 'B':
      binlog_enabled = 1;
      break;
    #endif
#endif
    case 'l':
      log_level = atoi (optarg);
      break;
    case 'f':
      sync_from_start = 1;
      break;
    case 'E':
      disable_auto_accept = 1;
      break;
    case 'w':
      allow_weak_random = 1;
      break;
#ifdef USE_LUA
    case 's':
      lua_file = strdup (optarg);
      break;
#endif
    case 'W':
      wait_dialog_list = 1;
      break;
#ifdef USE_PYTHON
    case 'Z':
      python_file = strdup (optarg);
      break;
#endif
    case 'C':
      disable_colors ++;
      break;
    case 'R':
      readline_disabled ++;
      break;
    case 'A':
      alert_sound = 1;
      break;
    case 'd':
      daemonize ++;
      break;
    case 'L':
      logname = optarg;
      break;
    case 'U':
      set_user_name = optarg;
      break;
    case 'G':
      set_group_name = optarg;
      break;
    case 'D':
      disable_output ++;
      break;
    case 'q':
      reset_authorization ++;
      break;
    case 'P':
      port = atoi (optarg);
      break;
    case 'S':
      unix_socket = optarg;
      break;
    case 'e':
      start_command = optarg;
      break;
    case 'I':
      use_ids ++;
      break;
    case '6':
      ipv6_enabled = 1;
      break;
    case 1002:
      disable_link_preview = 2;
      break;
    case 1003:
      enable_json = 1;
      break;
    case 1004:
      permanent_msg_id_mode = 1;
      break;
    case 1005:
      permanent_peer_id_mode = 1;
      break;
    case 'h':
    default:
      usage ();
      break;
    }
  }
}