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
typedef  int /*<<< orphan*/  robj ;
typedef  int /*<<< orphan*/  rio ;

/* Variables and functions */
 int /*<<< orphan*/  RDB_LOAD_ENC ; 
 int /*<<< orphan*/ * rdbGenericLoadStringObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

robj *rdbLoadEncodedStringObject(rio *rdb) {
    return rdbGenericLoadStringObject(rdb,RDB_LOAD_ENC,NULL);
}