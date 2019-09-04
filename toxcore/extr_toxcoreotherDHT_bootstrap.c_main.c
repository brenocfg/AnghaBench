#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_13__ {int /*<<< orphan*/  port; } ;
struct TYPE_12__ {TYPE_6__* net; int /*<<< orphan*/ * self_public_key; } ;
typedef  int /*<<< orphan*/  Onion_Announce ;
typedef  int /*<<< orphan*/  Onion ;
typedef  int /*<<< orphan*/  IP ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ DHT ;

/* Variables and functions */
 int DHT_bootstrap_from_address (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ DHT_isconnected (TYPE_1__*) ; 
 int LAN_DISCOVERY_INTERVAL ; 
 int /*<<< orphan*/  LANdiscovery_init (TYPE_1__*) ; 
 int /*<<< orphan*/  PORT ; 
 int /*<<< orphan*/  TOX_ENABLE_IPV6_DEFAULT ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  c_sleep (int) ; 
 int cmdline_parsefor_ipv46 (int,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_DHT (TYPE_1__*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hex_string_to_bin (char*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_timeout (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  manage_keys (TYPE_1__*) ; 
 int /*<<< orphan*/  networking_poll (TYPE_6__*) ; 
 TYPE_1__* new_DHT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_networking (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * new_onion (TYPE_1__*) ; 
 int /*<<< orphan*/ * new_onion_announce (TYPE_1__*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  send_LANdiscovery (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int) ; 
 int /*<<< orphan*/  unix_time () ; 

int main(int argc, char *argv[])
{
    if (argc == 2 && !strncasecmp(argv[1], "-h", 3)) {
        printf("Usage (connected)  : %s [--ipv4|--ipv6] IP PORT KEY\n", argv[0]);
        printf("Usage (unconnected): %s [--ipv4|--ipv6]\n", argv[0]);
        exit(0);
    }

    /* let user override default by cmdline */
    uint8_t ipv6enabled = TOX_ENABLE_IPV6_DEFAULT; /* x */
    int argvoffset = cmdline_parsefor_ipv46(argc, argv, &ipv6enabled);

    if (argvoffset < 0)
        exit(1);

    /* Initialize networking -
       Bind to ip 0.0.0.0 / [::] : PORT */
    IP ip;
    ip_init(&ip, ipv6enabled);

    DHT *dht = new_DHT(new_networking(ip, PORT));
    Onion *onion = new_onion(dht);
    Onion_Announce *onion_a = new_onion_announce(dht);

#ifdef DHT_NODE_EXTRA_PACKETS
    bootstrap_set_callbacks(dht->net, DHT_VERSION_NUMBER, DHT_MOTD, sizeof(DHT_MOTD));
#endif

    if (!(onion && onion_a)) {
        printf("Something failed to initialize.\n");
        exit(1);
    }

    perror("Initialization");

    manage_keys(dht);
    printf("Public key: ");
    uint32_t i;

#ifdef TCP_RELAY_ENABLED
#define NUM_PORTS 3
    uint16_t ports[NUM_PORTS] = {443, 3389, PORT};
    TCP_Server *tcp_s = new_TCP_server(ipv6enabled, NUM_PORTS, ports, dht->self_secret_key, onion);

    if (tcp_s == NULL) {
        printf("TCP server failed to initialize.\n");
        exit(1);
    }

#endif

    FILE *file;
    file = fopen("PUBLIC_ID.txt", "w");

    for (i = 0; i < 32; i++) {
        printf("%02hhX", dht->self_public_key[i]);
        fprintf(file, "%02hhX", dht->self_public_key[i]);
    }

    fclose(file);

    printf("\n");
    printf("Port: %u\n", ntohs(dht->net->port));

    if (argc > argvoffset + 3) {
        printf("Trying to bootstrap into the network...\n");
        uint16_t port = htons(atoi(argv[argvoffset + 2]));
        uint8_t *bootstrap_key = hex_string_to_bin(argv[argvoffset + 3]);
        int res = DHT_bootstrap_from_address(dht, argv[argvoffset + 1],
                                             ipv6enabled, port, bootstrap_key);
        free(bootstrap_key);

        if (!res) {
            printf("Failed to convert \"%s\" into an IP address. Exiting...\n", argv[argvoffset + 1]);
            exit(1);
        }
    }

    int is_waiting_for_dht_connection = 1;

    uint64_t last_LANdiscovery = 0;
    LANdiscovery_init(dht);

    while (1) {
        if (is_waiting_for_dht_connection && DHT_isconnected(dht)) {
            printf("Connected to other bootstrap node successfully.\n");
            is_waiting_for_dht_connection = 0;
        }

        do_DHT(dht);

        if (is_timeout(last_LANdiscovery, is_waiting_for_dht_connection ? 5 : LAN_DISCOVERY_INTERVAL)) {
            send_LANdiscovery(htons(PORT), dht);
            last_LANdiscovery = unix_time();
        }

#ifdef TCP_RELAY_ENABLED
        do_TCP_server(tcp_s);
#endif
        networking_poll(dht->net);

        c_sleep(1);
    }

    return 0;
}