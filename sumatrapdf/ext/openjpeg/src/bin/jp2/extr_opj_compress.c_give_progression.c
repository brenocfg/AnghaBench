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
typedef  int /*<<< orphan*/  OPJ_PROG_ORDER ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_CPRL ; 
 int /*<<< orphan*/  OPJ_LRCP ; 
 int /*<<< orphan*/  OPJ_PCRL ; 
 int /*<<< orphan*/  OPJ_PROG_UNKNOWN ; 
 int /*<<< orphan*/  OPJ_RLCP ; 
 int /*<<< orphan*/  OPJ_RPCL ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static OPJ_PROG_ORDER give_progression(const char progression[4])
{
    if (strncmp(progression, "LRCP", 4) == 0) {
        return OPJ_LRCP;
    }
    if (strncmp(progression, "RLCP", 4) == 0) {
        return OPJ_RLCP;
    }
    if (strncmp(progression, "RPCL", 4) == 0) {
        return OPJ_RPCL;
    }
    if (strncmp(progression, "PCRL", 4) == 0) {
        return OPJ_PCRL;
    }
    if (strncmp(progression, "CPRL", 4) == 0) {
        return OPJ_CPRL;
    }

    return OPJ_PROG_UNKNOWN;
}