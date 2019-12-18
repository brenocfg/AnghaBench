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
struct TYPE_2__ {long long length; int /*<<< orphan*/ * list; } ;
typedef  TYPE_1__ fsl_t ;
typedef  int /*<<< orphan*/  RedisModuleIO ;

/* Variables and functions */
 int /*<<< orphan*/  RedisModule_SaveSigned (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RedisModule_SaveUnsigned (int /*<<< orphan*/ *,long long) ; 

void fsl_rdb_save(RedisModuleIO *rdb, void *value) {
    fsl_t *fsl = value;
    RedisModule_SaveUnsigned(rdb,fsl->length);
    for (long long i = 0; i < fsl->length; i++)
        RedisModule_SaveSigned(rdb, fsl->list[i]);
}