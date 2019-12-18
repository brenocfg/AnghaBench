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
typedef  int /*<<< orphan*/  dict ;

/* Variables and functions */
 int /*<<< orphan*/  atomicDecr (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dictRelease (int /*<<< orphan*/ *) ; 
 size_t dictSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lazyfree_objects ; 

void lazyfreeFreeDatabaseFromBioThread(dict *ht1, dict *ht2) {
    size_t numkeys = dictSize(ht1);
    dictRelease(ht1);
    dictRelease(ht2);
    atomicDecr(lazyfree_objects,numkeys);
}