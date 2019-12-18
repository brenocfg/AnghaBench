#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ip_port; } ;
struct TYPE_7__ {TYPE_1__* paths; int /*<<< orphan*/ * path_creation_time; int /*<<< orphan*/ * last_path_success; } ;
struct TYPE_6__ {int /*<<< orphan*/  ip_port1; } ;
typedef  TYPE_2__ Onion_Client_Paths ;
typedef  TYPE_3__ Node_format ;

/* Variables and functions */
 unsigned int NUMBER_ONION_PATHS ; 
 int ONION_PATH_LENGTH ; 
 int /*<<< orphan*/  ONION_PATH_MAX_LIFETIME ; 
 int /*<<< orphan*/  ONION_PATH_TIMEOUT ; 
 scalar_t__ ipport_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ is_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_path_used(const Onion_Client_Paths *onion_paths, const Node_format *nodes)
{
    unsigned int i;

    for (i = 0; i < NUMBER_ONION_PATHS; ++i) {
        if (is_timeout(onion_paths->last_path_success[i], ONION_PATH_TIMEOUT)) {
            continue;
        }

        if (is_timeout(onion_paths->path_creation_time[i], ONION_PATH_MAX_LIFETIME)) {
            continue;
        }

        // TODO: do we really have to check it with the last node?
        if (ipport_equal(&onion_paths->paths[i].ip_port1, &nodes[ONION_PATH_LENGTH - 1].ip_port)) {
            return i;
        }
    }

    return -1;
}