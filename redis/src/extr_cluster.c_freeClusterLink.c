#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* node; int /*<<< orphan*/  rcvbuf; int /*<<< orphan*/  sndbuf; int /*<<< orphan*/ * conn; } ;
typedef  TYPE_2__ clusterLink ;
struct TYPE_5__ {int /*<<< orphan*/ * link; } ;

/* Variables and functions */
 int /*<<< orphan*/  connClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (TYPE_2__*) ; 

void freeClusterLink(clusterLink *link) {
    if (link->conn) {
        connClose(link->conn);
        link->conn = NULL;
    }
    sdsfree(link->sndbuf);
    sdsfree(link->rcvbuf);
    if (link->node)
        link->node->link = NULL;
    zfree(link);
}