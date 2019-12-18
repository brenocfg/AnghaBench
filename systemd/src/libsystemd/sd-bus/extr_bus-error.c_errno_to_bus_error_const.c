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
typedef  int /*<<< orphan*/  sd_bus_error ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ERROR_OOM ; 
#define  EACCES 145 
#define  EADDRINUSE 144 
#define  EADDRNOTAVAIL 143 
#define  EBADMSG 142 
#define  ECONNABORTED 141 
#define  ECONNRESET 140 
#define  EEXIST 139 
#define  EINVAL 138 
#define  EIO 137 
#define  ENETRESET 136 
#define  ENOBUFS 135 
#define  ENOENT 134 
#define  ENOMEM 133 
#define  EOPNOTSUPP 132 
#define  EPERM 131 
#define  ESRCH 130 
#define  ETIME 129 
#define  ETIMEDOUT 128 
 int /*<<< orphan*/  SD_BUS_ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  SD_BUS_ERROR_ADDRESS_IN_USE ; 
 int /*<<< orphan*/  SD_BUS_ERROR_BAD_ADDRESS ; 
 int /*<<< orphan*/  SD_BUS_ERROR_DISCONNECTED ; 
 int /*<<< orphan*/  SD_BUS_ERROR_FILE_EXISTS ; 
 int /*<<< orphan*/  SD_BUS_ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  SD_BUS_ERROR_INCONSISTENT_MESSAGE ; 
 int /*<<< orphan*/  SD_BUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  SD_BUS_ERROR_IO_ERROR ; 
 int /*<<< orphan*/  SD_BUS_ERROR_LIMITS_EXCEEDED ; 
 int /*<<< orphan*/  SD_BUS_ERROR_MAKE_CONST (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SD_BUS_ERROR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  SD_BUS_ERROR_NULL ; 
 int /*<<< orphan*/  SD_BUS_ERROR_TIMEOUT ; 
 int /*<<< orphan*/  SD_BUS_ERROR_UNIX_PROCESS_ID_UNKNOWN ; 

__attribute__((used)) static sd_bus_error errno_to_bus_error_const(int error) {

        if (error < 0)
                error = -error;

        switch (error) {

        case ENOMEM:
                return BUS_ERROR_OOM;

        case EPERM:
        case EACCES:
                return SD_BUS_ERROR_MAKE_CONST(SD_BUS_ERROR_ACCESS_DENIED, "Access denied");

        case EINVAL:
                return SD_BUS_ERROR_MAKE_CONST(SD_BUS_ERROR_INVALID_ARGS, "Invalid argument");

        case ESRCH:
                return SD_BUS_ERROR_MAKE_CONST(SD_BUS_ERROR_UNIX_PROCESS_ID_UNKNOWN, "No such process");

        case ENOENT:
                return SD_BUS_ERROR_MAKE_CONST(SD_BUS_ERROR_FILE_NOT_FOUND, "File not found");

        case EEXIST:
                return SD_BUS_ERROR_MAKE_CONST(SD_BUS_ERROR_FILE_EXISTS, "File exists");

        case ETIMEDOUT:
        case ETIME:
                return SD_BUS_ERROR_MAKE_CONST(SD_BUS_ERROR_TIMEOUT, "Timed out");

        case EIO:
                return SD_BUS_ERROR_MAKE_CONST(SD_BUS_ERROR_IO_ERROR, "Input/output error");

        case ENETRESET:
        case ECONNABORTED:
        case ECONNRESET:
                return SD_BUS_ERROR_MAKE_CONST(SD_BUS_ERROR_DISCONNECTED, "Disconnected");

        case EOPNOTSUPP:
                return SD_BUS_ERROR_MAKE_CONST(SD_BUS_ERROR_NOT_SUPPORTED, "Not supported");

        case EADDRNOTAVAIL:
                return SD_BUS_ERROR_MAKE_CONST(SD_BUS_ERROR_BAD_ADDRESS, "Address not available");

        case ENOBUFS:
                return SD_BUS_ERROR_MAKE_CONST(SD_BUS_ERROR_LIMITS_EXCEEDED, "Limits exceeded");

        case EADDRINUSE:
                return SD_BUS_ERROR_MAKE_CONST(SD_BUS_ERROR_ADDRESS_IN_USE, "Address in use");

        case EBADMSG:
                return SD_BUS_ERROR_MAKE_CONST(SD_BUS_ERROR_INCONSISTENT_MESSAGE, "Inconsistent message");
        }

        return SD_BUS_ERROR_NULL;
}