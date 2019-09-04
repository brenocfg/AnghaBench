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
struct TYPE_3__ {int /*<<< orphan*/  o; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ RedisModuleDigest ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xorDigest (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void RM_DigestEndSequence(RedisModuleDigest *md) {
    xorDigest(md->x,md->o,sizeof(md->o));
    memset(md->o,0,sizeof(md->o));
}