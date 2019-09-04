#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  char uint16_t ;
struct TYPE_11__ {int /*<<< orphan*/  net; int /*<<< orphan*/  self_public_key; int /*<<< orphan*/  self_secret_key; } ;
typedef  int /*<<< orphan*/  TCP_Server ;
typedef  int /*<<< orphan*/  Onion_Announce ;
typedef  int /*<<< orphan*/  Onion ;
typedef  int /*<<< orphan*/  Networking_Core ;
typedef  int /*<<< orphan*/  LOG_BACKEND ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_1__ DHT ;

/* Variables and functions */
 int /*<<< orphan*/  DAEMON_NAME ; 
 int /*<<< orphan*/  DAEMON_VERSION_NUMBER ; 
 scalar_t__ DHT_isconnected (TYPE_1__*) ; 
 int /*<<< orphan*/  LAN_DISCOVERY_INTERVAL ; 
 int /*<<< orphan*/  LANdiscovery_init (TYPE_1__*) ; 
 int /*<<< orphan*/  LOG_BACKEND_STDOUT ; 
 int /*<<< orphan*/  LOG_BACKEND_SYSLOG ; 
 int /*<<< orphan*/  LOG_LEVEL_ERROR ; 
 int /*<<< orphan*/  LOG_LEVEL_INFO ; 
 int /*<<< orphan*/  LOG_LEVEL_WARNING ; 
 int MAX_ALLOWED_PORT ; 
 int MIN_ALLOWED_PORT ; 
 int /*<<< orphan*/  SLEEP_MILLISECONDS (int) ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 scalar_t__ bootstrap_from_config (char*,TYPE_1__*,int) ; 
 scalar_t__ bootstrap_set_callbacks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  close_log () ; 
 int /*<<< orphan*/  daemonize (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  do_DHT (TYPE_1__*) ; 
 int /*<<< orphan*/  do_TCP_server (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_general_config (char*,char**,char**,int*,int*,int*,int*,int*,char**,int*,int*,char**) ; 
 int /*<<< orphan*/  handle_command_line_arguments (int,char**,char**,int /*<<< orphan*/ *,int*) ; 
 char htons (int) ; 
 int /*<<< orphan*/  ip_init (int /*<<< orphan*/ *,int) ; 
 scalar_t__ is_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 scalar_t__ manage_keys (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  networking_poll (int /*<<< orphan*/ ) ; 
 TYPE_1__* new_DHT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * new_TCP_server (int,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * new_networking (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * new_onion (TYPE_1__*) ; 
 int /*<<< orphan*/ * new_onion_announce (TYPE_1__*) ; 
 int /*<<< orphan*/  open_log (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_public_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_LANdiscovery (char const,TYPE_1__*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  umask (int) ; 
 int /*<<< orphan*/  unix_time () ; 
 int /*<<< orphan*/  write_log (int /*<<< orphan*/ ,char*,...) ; 

int main(int argc, char *argv[])
{
    umask(077);
    char *cfg_file_path;
    LOG_BACKEND log_backend;
    bool run_in_foreground;

    // choose backend for printing command line argument parsing output based on whether the daemon is being run from a terminal
    log_backend = isatty(STDOUT_FILENO) ? LOG_BACKEND_STDOUT : LOG_BACKEND_SYSLOG;

    open_log(log_backend);
    handle_command_line_arguments(argc, argv, &cfg_file_path, &log_backend, &run_in_foreground);
    close_log();

    open_log(log_backend);

    write_log(LOG_LEVEL_INFO, "Running \"%s\" version %lu.\n", DAEMON_NAME, DAEMON_VERSION_NUMBER);

    char *pid_file_path, *keys_file_path;
    int port;
    int enable_ipv6;
    int enable_ipv4_fallback;
    int enable_lan_discovery;
    int enable_tcp_relay;
    uint16_t *tcp_relay_ports;
    int tcp_relay_port_count;
    int enable_motd;
    char *motd;

    if (get_general_config(cfg_file_path, &pid_file_path, &keys_file_path, &port, &enable_ipv6, &enable_ipv4_fallback,
                           &enable_lan_discovery, &enable_tcp_relay, &tcp_relay_ports, &tcp_relay_port_count, &enable_motd, &motd)) {
        write_log(LOG_LEVEL_INFO, "General config read successfully\n");
    } else {
        write_log(LOG_LEVEL_ERROR, "Couldn't read config file: %s. Exiting.\n", cfg_file_path);
        return 1;
    }

    if (port < MIN_ALLOWED_PORT || port > MAX_ALLOWED_PORT) {
        write_log(LOG_LEVEL_ERROR, "Invalid port: %d, should be in [%d, %d]. Exiting.\n", port, MIN_ALLOWED_PORT,
                  MAX_ALLOWED_PORT);
        return 1;
    }

    if (!run_in_foreground) {
        daemonize(log_backend, pid_file_path);
    }

    free(pid_file_path);

    IP ip;
    ip_init(&ip, enable_ipv6);

    Networking_Core *net = new_networking(ip, port);

    if (net == NULL) {
        if (enable_ipv6 && enable_ipv4_fallback) {
            write_log(LOG_LEVEL_WARNING, "Couldn't initialize IPv6 networking. Falling back to using IPv4.\n");
            enable_ipv6 = 0;
            ip_init(&ip, enable_ipv6);
            net = new_networking(ip, port);

            if (net == NULL) {
                write_log(LOG_LEVEL_ERROR, "Couldn't fallback to IPv4. Exiting.\n");
                return 1;
            }
        } else {
            write_log(LOG_LEVEL_ERROR, "Couldn't initialize networking. Exiting.\n");
            return 1;
        }
    }

    DHT *dht = new_DHT(net);

    if (dht == NULL) {
        write_log(LOG_LEVEL_ERROR, "Couldn't initialize Tox DHT instance. Exiting.\n");
        return 1;
    }

    Onion *onion = new_onion(dht);
    Onion_Announce *onion_a = new_onion_announce(dht);

    if (!(onion && onion_a)) {
        write_log(LOG_LEVEL_ERROR, "Couldn't initialize Tox Onion. Exiting.\n");
        return 1;
    }

    if (enable_motd) {
        if (bootstrap_set_callbacks(dht->net, DAEMON_VERSION_NUMBER, (uint8_t *)motd, strlen(motd) + 1) == 0) {
            write_log(LOG_LEVEL_INFO, "Set MOTD successfully.\n");
        } else {
            write_log(LOG_LEVEL_ERROR, "Couldn't set MOTD: %s. Exiting.\n", motd);
            return 1;
        }

        free(motd);
    }

    if (manage_keys(dht, keys_file_path)) {
        write_log(LOG_LEVEL_INFO, "Keys are managed successfully.\n");
    } else {
        write_log(LOG_LEVEL_ERROR, "Couldn't read/write: %s. Exiting.\n", keys_file_path);
        return 1;
    }

    free(keys_file_path);

    TCP_Server *tcp_server = NULL;

    if (enable_tcp_relay) {
        if (tcp_relay_port_count == 0) {
            write_log(LOG_LEVEL_ERROR, "No TCP relay ports read. Exiting.\n");
            return 1;
        }

        tcp_server = new_TCP_server(enable_ipv6, tcp_relay_port_count, tcp_relay_ports, dht->self_secret_key, onion);

        // tcp_relay_port_count != 0 at this point
        free(tcp_relay_ports);

        if (tcp_server != NULL) {
            write_log(LOG_LEVEL_INFO, "Initialized Tox TCP server successfully.\n");
        } else {
            write_log(LOG_LEVEL_ERROR, "Couldn't initialize Tox TCP server. Exiting.\n");
            return 1;
        }
    }

    if (bootstrap_from_config(cfg_file_path, dht, enable_ipv6)) {
        write_log(LOG_LEVEL_INFO, "List of bootstrap nodes read successfully.\n");
    } else {
        write_log(LOG_LEVEL_ERROR, "Couldn't read list of bootstrap nodes in %s. Exiting.\n", cfg_file_path);
        return 1;
    }

    print_public_key(dht->self_public_key);

    uint64_t last_LANdiscovery = 0;
    const uint16_t htons_port = htons(port);

    int waiting_for_dht_connection = 1;

    if (enable_lan_discovery) {
        LANdiscovery_init(dht);
        write_log(LOG_LEVEL_INFO, "Initialized LAN discovery successfully.\n");
    }

    while (1) {
        do_DHT(dht);

        if (enable_lan_discovery && is_timeout(last_LANdiscovery, LAN_DISCOVERY_INTERVAL)) {
            send_LANdiscovery(htons_port, dht);
            last_LANdiscovery = unix_time();
        }

        if (enable_tcp_relay) {
            do_TCP_server(tcp_server);
        }

        networking_poll(dht->net);

        if (waiting_for_dht_connection && DHT_isconnected(dht)) {
            write_log(LOG_LEVEL_INFO, "Connected to another bootstrap node successfully.\n");
            waiting_for_dht_connection = 0;
        }

        SLEEP_MILLISECONDS(30);
    }

    return 1;
}