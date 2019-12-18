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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  robj ;
typedef  int /*<<< orphan*/  rio ;

/* Variables and functions */
 int /*<<< orphan*/  RDB_LOAD_NONE ; 
 scalar_t__ RDB_MODULE_OPCODE_DOUBLE ; 
 scalar_t__ RDB_MODULE_OPCODE_EOF ; 
 scalar_t__ RDB_MODULE_OPCODE_FLOAT ; 
 scalar_t__ RDB_MODULE_OPCODE_SINT ; 
 scalar_t__ RDB_MODULE_OPCODE_STRING ; 
 scalar_t__ RDB_MODULE_OPCODE_UINT ; 
 int /*<<< orphan*/ * createStringObject (char*,int) ; 
 int /*<<< orphan*/  decrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdbExitReportCorruptRDB (char*,char*) ; 
 int /*<<< orphan*/ * rdbGenericLoadStringObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rdbLoadBinaryDoubleValue (int /*<<< orphan*/ *,double*) ; 
 int rdbLoadBinaryFloatValue (int /*<<< orphan*/ *,float*) ; 
 scalar_t__ rdbLoadLen (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rdbLoadLenByRef (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 

robj *rdbLoadCheckModuleValue(rio *rdb, char *modulename) {
    uint64_t opcode;
    while((opcode = rdbLoadLen(rdb,NULL)) != RDB_MODULE_OPCODE_EOF) {
        if (opcode == RDB_MODULE_OPCODE_SINT ||
            opcode == RDB_MODULE_OPCODE_UINT)
        {
            uint64_t len;
            if (rdbLoadLenByRef(rdb,NULL,&len) == -1) {
                rdbExitReportCorruptRDB(
                    "Error reading integer from module %s value", modulename);
            }
        } else if (opcode == RDB_MODULE_OPCODE_STRING) {
            robj *o = rdbGenericLoadStringObject(rdb,RDB_LOAD_NONE,NULL);
            if (o == NULL) {
                rdbExitReportCorruptRDB(
                    "Error reading string from module %s value", modulename);
            }
            decrRefCount(o);
        } else if (opcode == RDB_MODULE_OPCODE_FLOAT) {
            float val;
            if (rdbLoadBinaryFloatValue(rdb,&val) == -1) {
                rdbExitReportCorruptRDB(
                    "Error reading float from module %s value", modulename);
            }
        } else if (opcode == RDB_MODULE_OPCODE_DOUBLE) {
            double val;
            if (rdbLoadBinaryDoubleValue(rdb,&val) == -1) {
                rdbExitReportCorruptRDB(
                    "Error reading double from module %s value", modulename);
            }
        }
    }
    return createStringObject("module-dummy-value",18);
}