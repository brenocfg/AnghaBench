#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  patterns; int /*<<< orphan*/  passwords; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ user ;

/* Variables and functions */
 int /*<<< orphan*/  ACLResetSubcommands (TYPE_1__*) ; 
 int /*<<< orphan*/  listRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (TYPE_1__*) ; 

void ACLFreeUser(user *u) {
    sdsfree(u->name);
    listRelease(u->passwords);
    listRelease(u->patterns);
    ACLResetSubcommands(u);
    zfree(u);
}