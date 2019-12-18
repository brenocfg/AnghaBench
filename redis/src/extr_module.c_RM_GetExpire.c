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
typedef  int mstime_t ;
struct TYPE_3__ {int /*<<< orphan*/ * value; int /*<<< orphan*/  key; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ RedisModuleKey ;

/* Variables and functions */
 int getExpire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mstime () ; 

mstime_t RM_GetExpire(RedisModuleKey *key) {
    mstime_t expire = getExpire(key->db,key->key);
    if (expire == -1 || key->value == NULL) return -1;
    expire -= mstime();
    return expire >= 0 ? expire : 0;
}