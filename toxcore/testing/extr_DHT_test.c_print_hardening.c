#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  testing_pingedid; scalar_t__ testing_timestamp; int /*<<< orphan*/  testing_requests; int /*<<< orphan*/  send_nodes_pingedid; scalar_t__ send_nodes_timestamp; int /*<<< orphan*/  send_nodes_ok; int /*<<< orphan*/  routes_requests_pingedid; scalar_t__ routes_requests_timestamp; int /*<<< orphan*/  routes_requests_ok; } ;
typedef  TYPE_1__ Hardening ;

/* Variables and functions */
 int /*<<< orphan*/  print_client_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void print_hardening(Hardening *h)
{
    printf("Hardening:\n");
    printf("routes_requests_ok: %hhu\n", h->routes_requests_ok);
    printf("routes_requests_timestamp: %llu\n", (long long unsigned int)h->routes_requests_timestamp);
    printf("routes_requests_pingedid: ");
    print_client_id(h->routes_requests_pingedid);
    printf("\nsend_nodes_ok: %hhu\n", h->send_nodes_ok);
    printf("send_nodes_timestamp: %llu\n", (long long unsigned int)h->send_nodes_timestamp);
    printf("send_nodes_pingedid: ");
    print_client_id(h->send_nodes_pingedid);
    printf("\ntesting_requests: %hhu\n", h->testing_requests);
    printf("testing_timestamp: %llu\n", (long long unsigned int)h->testing_timestamp);
    printf("testing_pingedid: ");
    print_client_id(h->testing_pingedid);
    printf("\n\n");
}