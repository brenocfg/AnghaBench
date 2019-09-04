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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  Node_format ;
typedef  int /*<<< orphan*/  DHT ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_TYPE_GETNODE_REQ ; 
 int crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int send_hardening_req (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int send_hardening_getnode_req(DHT *dht, Node_format *dest, Node_format *node_totest, uint8_t *search_id)
{
    uint8_t data[sizeof(Node_format) + crypto_box_PUBLICKEYBYTES];
    memcpy(data, node_totest, sizeof(Node_format));
    memcpy(data + sizeof(Node_format), search_id, crypto_box_PUBLICKEYBYTES);
    return send_hardening_req(dht, dest, CHECK_TYPE_GETNODE_REQ, data, sizeof(Node_format) + crypto_box_PUBLICKEYBYTES);
}