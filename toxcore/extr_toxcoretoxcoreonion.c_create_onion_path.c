#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int /*<<< orphan*/ * self_public_key; int /*<<< orphan*/ * self_secret_key; } ;
struct TYPE_8__ {int /*<<< orphan*/ * public_key; int /*<<< orphan*/  ip_port; } ;
struct TYPE_7__ {int /*<<< orphan*/  node_public_key3; int /*<<< orphan*/  node_public_key2; int /*<<< orphan*/  node_public_key1; int /*<<< orphan*/  ip_port3; int /*<<< orphan*/  ip_port2; int /*<<< orphan*/  ip_port1; int /*<<< orphan*/  public_key3; int /*<<< orphan*/  shared_key3; int /*<<< orphan*/  public_key2; int /*<<< orphan*/  shared_key2; int /*<<< orphan*/  public_key1; int /*<<< orphan*/  shared_key1; } ;
typedef  TYPE_1__ Onion_Path ;
typedef  TYPE_2__ Node_format ;
typedef  TYPE_3__ DHT ;

/* Variables and functions */
 int crypto_box_PUBLICKEYBYTES ; 
 int crypto_box_SECRETKEYBYTES ; 
 int /*<<< orphan*/  crypto_box_keypair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encrypt_precompute (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int create_onion_path(const DHT *dht, Onion_Path *new_path, const Node_format *nodes)
{
    if (!new_path || !nodes)
        return -1;

    encrypt_precompute(nodes[0].public_key, dht->self_secret_key, new_path->shared_key1);
    memcpy(new_path->public_key1, dht->self_public_key, crypto_box_PUBLICKEYBYTES);

    uint8_t random_public_key[crypto_box_PUBLICKEYBYTES];
    uint8_t random_secret_key[crypto_box_SECRETKEYBYTES];

    crypto_box_keypair(random_public_key, random_secret_key);
    encrypt_precompute(nodes[1].public_key, random_secret_key, new_path->shared_key2);
    memcpy(new_path->public_key2, random_public_key, crypto_box_PUBLICKEYBYTES);

    crypto_box_keypair(random_public_key, random_secret_key);
    encrypt_precompute(nodes[2].public_key, random_secret_key, new_path->shared_key3);
    memcpy(new_path->public_key3, random_public_key, crypto_box_PUBLICKEYBYTES);

    new_path->ip_port1 = nodes[0].ip_port;
    new_path->ip_port2 = nodes[1].ip_port;
    new_path->ip_port3 = nodes[2].ip_port;

    memcpy(new_path->node_public_key1, nodes[0].public_key, crypto_box_PUBLICKEYBYTES);
    memcpy(new_path->node_public_key2, nodes[1].public_key, crypto_box_PUBLICKEYBYTES);
    memcpy(new_path->node_public_key3, nodes[2].public_key, crypto_box_PUBLICKEYBYTES);

    return 0;
}