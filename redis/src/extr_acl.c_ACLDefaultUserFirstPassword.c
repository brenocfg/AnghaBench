#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * sds ;
typedef  int /*<<< orphan*/  listNode ;
struct TYPE_2__ {int /*<<< orphan*/  passwords; } ;

/* Variables and functions */
 TYPE_1__* DefaultUser ; 
 int /*<<< orphan*/ * listFirst (int /*<<< orphan*/ ) ; 
 scalar_t__ listLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * listNodeValue (int /*<<< orphan*/ *) ; 

sds ACLDefaultUserFirstPassword(void) {
    if (listLength(DefaultUser->passwords) == 0) return NULL;
    listNode *first = listFirst(DefaultUser->passwords);
    return listNodeValue(first);
}