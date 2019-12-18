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
struct TYPE_3__ {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  secret_symmetric_key; } ;
typedef  TYPE_1__ Onion ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_REFRESH_INTERVAL ; 
 scalar_t__ is_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_symmetric_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unix_time () ; 

__attribute__((used)) static void change_symmetric_key(Onion *onion)
{
    if (is_timeout(onion->timestamp, KEY_REFRESH_INTERVAL)) {
        new_symmetric_key(onion->secret_symmetric_key);
        onion->timestamp = unix_time();
    }
}