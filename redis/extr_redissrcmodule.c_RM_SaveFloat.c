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
struct TYPE_3__ {int error; int bytes; int /*<<< orphan*/  rio; } ;
typedef  TYPE_1__ RedisModuleIO ;

/* Variables and functions */
 int /*<<< orphan*/  RDB_MODULE_OPCODE_FLOAT ; 
 int rdbSaveBinaryFloatValue (int /*<<< orphan*/ ,float) ; 
 int rdbSaveLen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void RM_SaveFloat(RedisModuleIO *io, float value) {
    if (io->error) return;
    /* Save opcode. */
    int retval = rdbSaveLen(io->rio, RDB_MODULE_OPCODE_FLOAT);
    if (retval == -1) goto saveerr;
    io->bytes += retval;
    /* Save value. */
    retval = rdbSaveBinaryFloatValue(io->rio, value);
    if (retval == -1) goto saveerr;
    io->bytes += retval;
    return;

saveerr:
    io->error = 1;
}