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
struct TYPE_3__ {int /*<<< orphan*/  pubsub_patterns; int /*<<< orphan*/  pubsub_channels; } ;
typedef  TYPE_1__ client ;

/* Variables and functions */
 int dictSize (int /*<<< orphan*/ ) ; 
 int listLength (int /*<<< orphan*/ ) ; 

int clientSubscriptionsCount(client *c) {
    return dictSize(c->pubsub_channels)+
           listLength(c->pubsub_patterns);
}