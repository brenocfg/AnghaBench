#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  size_t uint16_t ;
struct TYPE_10__ {TYPE_2__* friends_list; int /*<<< orphan*/  ping; } ;
struct TYPE_9__ {void* port; int /*<<< orphan*/  ip; } ;
struct TYPE_7__ {int punching_index; scalar_t__ tries; int punching_index2; } ;
struct TYPE_8__ {TYPE_1__ nat; int /*<<< orphan*/  public_key; } ;
typedef  TYPE_3__ IP_Port ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_4__ DHT ;

/* Variables and functions */
 size_t MAX_FRIEND_CLIENTS ; 
 scalar_t__ MAX_NORMAL_PUNCHING_TRIES ; 
 int MAX_PUNCHING_PORTS ; 
 void* htons (size_t) ; 
 int /*<<< orphan*/  ip_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_ping_request (int /*<<< orphan*/ ,TYPE_3__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void punch_holes(DHT *dht, IP ip, uint16_t *port_list, uint16_t numports, uint16_t friend_num)
{
    if (numports > MAX_FRIEND_CLIENTS || numports == 0)
        return;

    uint32_t i;
    uint32_t top = dht->friends_list[friend_num].nat.punching_index + MAX_PUNCHING_PORTS;
    uint16_t firstport = port_list[0];

    for (i = 0; i < numports; ++i) {
        if (firstport != port_list[i])
            break;
    }

    if (i == numports) { /* If all ports are the same, only try that one port. */
        IP_Port pinging;
        ip_copy(&pinging.ip, &ip);
        pinging.port = htons(firstport);
        send_ping_request(dht->ping, pinging, dht->friends_list[friend_num].public_key);
    } else {
        for (i = dht->friends_list[friend_num].nat.punching_index; i != top; ++i) {
            /* TODO: Improve port guessing algorithm. */
            uint16_t port = port_list[(i / 2) % numports] + (i / (2 * numports)) * ((i % 2) ? -1 : 1);
            IP_Port pinging;
            ip_copy(&pinging.ip, &ip);
            pinging.port = htons(port);
            send_ping_request(dht->ping, pinging, dht->friends_list[friend_num].public_key);
        }

        dht->friends_list[friend_num].nat.punching_index = i;
    }

    if (dht->friends_list[friend_num].nat.tries > MAX_NORMAL_PUNCHING_TRIES) {
        top = dht->friends_list[friend_num].nat.punching_index2 + MAX_PUNCHING_PORTS;
        uint16_t port = 1024;
        IP_Port pinging;
        ip_copy(&pinging.ip, &ip);

        for (i = dht->friends_list[friend_num].nat.punching_index2; i != top; ++i) {
            pinging.port = htons(port + i);
            send_ping_request(dht->ping, pinging, dht->friends_list[friend_num].public_key);
        }

        dht->friends_list[friend_num].nat.punching_index2 = i - (MAX_PUNCHING_PORTS / 2);
    }

    ++dht->friends_list[friend_num].nat.tries;
}