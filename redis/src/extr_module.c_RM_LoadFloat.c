#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {int ver; int /*<<< orphan*/  rio; scalar_t__ error; } ;
typedef  TYPE_1__ RedisModuleIO ;

/* Variables and functions */
 scalar_t__ RDB_MODULE_OPCODE_FLOAT ; 
 int /*<<< orphan*/  moduleRDBLoadError (TYPE_1__*) ; 
 int rdbLoadBinaryFloatValue (int /*<<< orphan*/ ,float*) ; 
 scalar_t__ rdbLoadLen (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

float RM_LoadFloat(RedisModuleIO *io) {
    if (io->error) return 0;
    if (io->ver == 2) {
        uint64_t opcode = rdbLoadLen(io->rio,NULL);
        if (opcode != RDB_MODULE_OPCODE_FLOAT) goto loaderr;
    }
    float value;
    int retval = rdbLoadBinaryFloatValue(io->rio, &value);
    if (retval == -1) goto loaderr;
    return value;

loaderr:
    moduleRDBLoadError(io);
    return 0;
}