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
 int /*<<< orphan*/  CPRL ; 
 int /*<<< orphan*/  LRCP ; 
 int /*<<< orphan*/  PCRL ; 
 int /*<<< orphan*/  PROG_UNKNOWN ; 
 int /*<<< orphan*/  RLCP ; 
 int /*<<< orphan*/  RPCL ; 
 scalar_t__ strncmp (char*,char*,int) ; 

OPJ_PROG_ORDER give_progression(char progression[4])
{
    if (strncmp(progression, "LRCP", 4) == 0) {
        return LRCP;
    }
    if (strncmp(progression, "RLCP", 4) == 0) {
        return RLCP;
    }
    if (strncmp(progression, "RPCL", 4) == 0) {
        return RPCL;
    }
    if (strncmp(progression, "PCRL", 4) == 0) {
        return PCRL;
    }
    if (strncmp(progression, "CPRL", 4) == 0) {
        return CPRL;
    }

    return PROG_UNKNOWN;
}