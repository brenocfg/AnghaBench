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
 char* PROGNAME ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void usage (void) {
  printf ("%s Usage\n", PROGNAME);
    
  printf ("  --phone/-u                           specify username (would not be asked during authorization)\n");
  printf ("  --rsa-key/-k                         specify location of public key (possible multiple entries)\n");
  printf ("  --verbosity/-v                       increase verbosity (0-ERROR 1-WARNIN 2-NOTICE 3+-DEBUG-levels)\n");
  printf ("  --enable-msg-id/-N                   message num mode\n");
  #ifdef HAVE_LIBCONFIG
  printf ("  --config/-c                          config file name\n");
  printf ("  --profile/-p                         use specified profile\n");
  #else
  #if 0
  printf ("  --enable-binlog/-B                   enable binlog\n");
  #endif
  #endif
  printf ("  --log-level/-l                       log level\n");
  printf ("  --sync-from-start/-f                 during authorization fetch all messages since registration\n");
  printf ("  --disable-auto-accept/-E             disable auto accept of encrypted chats\n");
  #ifdef USE_LUA
  printf ("  --lua-script/-s                      lua script file\n");
  #endif
  printf ("  --wait-dialog-list/-W                send dialog_list query and wait for answer before reading input\n");
  printf ("  --disable-colors/-C                  disable color output\n");
  printf ("  --disable-readline/-R                disable readline\n");
  printf ("  --alert/-A                           enable bell notifications\n");
  printf ("  --daemonize/-d                       daemon mode\n");
  printf ("  --logname/-L <log-name>              log file name\n");
  printf ("  --username/-U <user-name>            change uid after start\n");
  printf ("  --groupname/-G <group-name>          change gid after start\n");
  printf ("  --disable-output/-D                  disable output\n");
  printf ("  --tcp-port/-P <port>                 port to listen for input commands\n");
  printf ("  --udp-socket/-S <socket-name>        unix socket to create\n");
  printf ("  --exec/-e <commands>                 make commands end exit\n");
  printf ("  --disable-names/-I                   use user and chat IDs in updates instead of names\n");
  printf ("  --enable-ipv6/-6                     use ipv6 (may be unstable)\n");
  printf ("  --help/-h                            prints this help\n");
  printf ("  --accept-any-tcp                     accepts tcp connections from any src (only loopback by default)\n");
  printf ("  --disable-link-preview               disables server-side previews to links\n");
  printf ("  --bot/-b                             bot mode\n");  
  #ifdef USE_JSON
  printf ("  --json                               prints answers and values in json format\n");
  #endif
  #ifdef USE_PYTHON
  printf ("  --python-script/-Z <script-name>     python script file\n");
  #endif
  printf ("  --permanent-msg-ids                  use permanent msg ids\n");
  printf ("  --permanent-peer-ids                 use permanent peer ids\n");

  exit (1);
}