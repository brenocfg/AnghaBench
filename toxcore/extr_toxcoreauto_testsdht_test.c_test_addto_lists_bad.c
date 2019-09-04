#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  public_key ;
struct TYPE_11__ {int /*<<< orphan*/  assoc4; int /*<<< orphan*/  assoc6; int /*<<< orphan*/  public_key; } ;
struct TYPE_9__ {scalar_t__ family; } ;
struct TYPE_10__ {int port; TYPE_1__ ip; } ;
typedef  TYPE_2__ IP_Port ;
typedef  int /*<<< orphan*/  DHT ;
typedef  TYPE_3__ Client_data ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int addto_lists (int /*<<< orphan*/ *,TYPE_2__,int*) ; 
 int /*<<< orphan*/  ck_assert_msg (int,char*) ; 
 scalar_t__ client_in_list (TYPE_3__*,int,int*) ; 
 int crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  id_copy (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_all_good (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  mark_bad (int /*<<< orphan*/ *) ; 
 int rand () ; 
 int /*<<< orphan*/  randombytes (int*,int) ; 

void test_addto_lists_bad(DHT            *dht,
                          Client_data    *list,
                          uint32_t        length,
                          IP_Port        *ip_port)
{
    // check "bad" clients replacement
    int used, test1, test2, test3;
    uint8_t public_key[crypto_box_PUBLICKEYBYTES], test_id1[crypto_box_PUBLICKEYBYTES], test_id2[crypto_box_PUBLICKEYBYTES],
            test_id3[crypto_box_PUBLICKEYBYTES];
    uint8_t ipv6 = ip_port->ip.family == AF_INET6 ? 1 : 0;

    randombytes(public_key, sizeof(public_key));
    mark_all_good(list, length, ipv6);

    test1 = rand() % (length / 3);
    test2 = rand() % (length / 3) + length / 3;
    test3 = rand() % (length / 3) + 2 * length / 3;
    ck_assert_msg(!(test1 == test2 || test1 == test3 || test2 == test3), "Wrong test indices are chosen");

    id_copy((uint8_t *)&test_id1, list[test1].public_key);
    id_copy((uint8_t *)&test_id2, list[test2].public_key);
    id_copy((uint8_t *)&test_id3, list[test3].public_key);

    // mark nodes as "bad"
    if (ipv6) {
        mark_bad(&list[test1].assoc6);
        mark_bad(&list[test2].assoc6);
        mark_bad(&list[test3].assoc6);
    } else {
        mark_bad(&list[test1].assoc4);
        mark_bad(&list[test2].assoc4);
        mark_bad(&list[test3].assoc4);
    }

    ip_port->port += 1;
    used = addto_lists(dht, *ip_port, public_key);
    ck_assert_msg(used >= 1, "Wrong number of added clients");

    ck_assert_msg(client_in_list(list, length, public_key) >= 0, "Client id is not in the list");
    ck_assert_msg(client_in_list(list, length, test_id2) >= 0, "Wrong bad client removed");
    ck_assert_msg(client_in_list(list, length, test_id3) >= 0, "Wrong bad client removed");
}