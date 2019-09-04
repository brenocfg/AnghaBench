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
struct test_tcp_txcounters {struct test_tcp_txcounters* next; int /*<<< orphan*/  ip_addr; int /*<<< orphan*/  netmask; int /*<<< orphan*/  flags; int /*<<< orphan*/  output; struct test_tcp_txcounters* state; } ;
struct netif {struct netif* next; int /*<<< orphan*/  ip_addr; int /*<<< orphan*/  netmask; int /*<<< orphan*/  flags; int /*<<< orphan*/  output; struct netif* state; } ;
typedef  int /*<<< orphan*/  ip_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETIF_FLAG_UP ; 
 int /*<<< orphan*/  ip_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct test_tcp_txcounters*,int /*<<< orphan*/ ,int) ; 
 struct test_tcp_txcounters* netif_list ; 
 int /*<<< orphan*/  test_tcp_netif_output ; 

void test_tcp_init_netif(struct netif *netif, struct test_tcp_txcounters *txcounters,
                         ip_addr_t *ip_addr, ip_addr_t *netmask)
{
  struct netif *n;
  memset(netif, 0, sizeof(struct netif));
  if (txcounters != NULL) {
    memset(txcounters, 0, sizeof(struct test_tcp_txcounters));
    netif->state = txcounters;
  }
  netif->output = test_tcp_netif_output;
  netif->flags |= NETIF_FLAG_UP;
  ip_addr_copy(netif->netmask, *netmask);
  ip_addr_copy(netif->ip_addr, *ip_addr);
  for (n = netif_list; n != NULL; n = n->next) {
    if (n == netif) {
      return;
    }
  }
  netif->next = NULL;
  netif_list = netif;
}