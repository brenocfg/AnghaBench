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
typedef  int ssize_t ;
struct TYPE_3__ {int error; int bytes; int /*<<< orphan*/  rio; } ;
typedef  TYPE_1__ RedisModuleIO ;

/* Variables and functions */
 int /*<<< orphan*/  RDB_MODULE_OPCODE_STRING ; 
 int rdbSaveLen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdbSaveRawString (int /*<<< orphan*/ ,unsigned char*,size_t) ; 

void RM_SaveStringBuffer(RedisModuleIO *io, const char *str, size_t len) {
    if (io->error) return;
    /* Save opcode. */
    ssize_t retval = rdbSaveLen(io->rio, RDB_MODULE_OPCODE_STRING);
    if (retval == -1) goto saveerr;
    io->bytes += retval;
    /* Save value. */
    retval = rdbSaveRawString(io->rio, (unsigned char*)str,len);
    if (retval == -1) goto saveerr;
    io->bytes += retval;
    return;

saveerr:
    io->error = 1;
}