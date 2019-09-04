#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  public_key ;
struct TYPE_16__ {int num_friends; TYPE_1__* friends_list; int /*<<< orphan*/  self_public_key; int /*<<< orphan*/  close_clientlist; } ;
struct TYPE_15__ {int port; int /*<<< orphan*/  ip; } ;
struct TYPE_14__ {int /*<<< orphan*/  public_key; int /*<<< orphan*/  client_list; } ;
typedef  int /*<<< orphan*/  Networking_Core ;
typedef  TYPE_2__ IP_Port ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_3__ DHT ;

/* Variables and functions */
 int /*<<< orphan*/  LCLIENT_LIST ; 
 int MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_FRIEND_CLIENTS ; 
 int TOX_PORT_DEFAULT ; 
 int addto_lists (TYPE_3__*,TYPE_2__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ck_assert_msg (int,char*) ; 
 int crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  kill_DHT (TYPE_3__*) ; 
 int /*<<< orphan*/  kill_networking (int /*<<< orphan*/ *) ; 
 TYPE_3__* new_DHT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * new_networking (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  randombytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_addto_lists_bad (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  test_addto_lists_good (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_addto_lists_update (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

void test_addto_lists(IP ip)
{
    Networking_Core *net = new_networking(ip, TOX_PORT_DEFAULT);
    ck_assert_msg(net != 0, "Failed to create Networking_Core");

    DHT *dht = new_DHT(net);
    ck_assert_msg(dht != 0, "Failed to create DHT");

    IP_Port ip_port = { .ip = ip, .port = TOX_PORT_DEFAULT };
    uint8_t public_key[crypto_box_PUBLICKEYBYTES];
    int i, used;

    // check lists filling
    for (i = 0; i < MAX(LCLIENT_LIST, MAX_FRIEND_CLIENTS); ++i) {
        randombytes(public_key, sizeof(public_key));
        used = addto_lists(dht, ip_port, public_key);
        ck_assert_msg(used == dht->num_friends + 1, "Wrong number of added clients with existing ip_port");
    }

    for (i = 0; i < MAX(LCLIENT_LIST, MAX_FRIEND_CLIENTS); ++i) {
        ip_port.port += 1;
        used = addto_lists(dht, ip_port, public_key);
        ck_assert_msg(used == dht->num_friends + 1, "Wrong number of added clients with existing public_key");
    }

    for (i = 0; i < MAX(LCLIENT_LIST, MAX_FRIEND_CLIENTS); ++i) {
        ip_port.port += 1;
        randombytes(public_key, sizeof(public_key));
        used = addto_lists(dht, ip_port, public_key);
        ck_assert_msg(used >= 1, "Wrong number of added clients");
    }

    /*check: Current behavior if there are two clients with the same id is
     * to replace the first ip by the second. */
    test_addto_lists_update(dht, dht->close_clientlist, LCLIENT_LIST, &ip_port);

    for (i = 0; i < dht->num_friends; ++i)
        test_addto_lists_update(dht, dht->friends_list[i].client_list, MAX_FRIEND_CLIENTS, &ip_port);

    // check "bad" entries
    test_addto_lists_bad(dht, dht->close_clientlist, LCLIENT_LIST, &ip_port);

    for (i = 0; i < dht->num_friends; ++i)
        test_addto_lists_bad(dht, dht->friends_list[i].client_list, MAX_FRIEND_CLIENTS, &ip_port);

    // check "possibly bad" entries
    /*
    test_addto_lists_possible_bad(dht, dht->close_clientlist, LCLIENT_LIST, &ip_port, dht->self_public_key);

    for (i = 0; i < dht->num_friends; ++i)
        test_addto_lists_possible_bad(dht, dht->friends_list[i].client_list, MAX_FRIEND_CLIENTS, &ip_port,
                                      dht->friends_list[i].public_key);
    */
    // check "good" entries
    test_addto_lists_good(dht, dht->close_clientlist, LCLIENT_LIST, &ip_port, dht->self_public_key);

    for (i = 0; i < dht->num_friends; ++i)
        test_addto_lists_good(dht, dht->friends_list[i].client_list, MAX_FRIEND_CLIENTS, &ip_port,
                              dht->friends_list[i].public_key);

    kill_DHT(dht);
    kill_networking(net);
}