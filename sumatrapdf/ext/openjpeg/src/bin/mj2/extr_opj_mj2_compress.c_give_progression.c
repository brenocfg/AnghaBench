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

__attribute__((used)) static OPJ_PROG_ORDER give_progression(const char progression[5])
{
    if (progression[0] == 'L' && progression[1] == 'R'
            && progression[2] == 'C' && progression[3] == 'P') {
        return LRCP;
    } else {
        if (progression[0] == 'R' && progression[1] == 'L'
                && progression[2] == 'C' && progression[3] == 'P') {
            return RLCP;
        } else {
            if (progression[0] == 'R' && progression[1] == 'P'
                    && progression[2] == 'C' && progression[3] == 'L') {
                return RPCL;
            } else {
                if (progression[0] == 'P' && progression[1] == 'C'
                        && progression[2] == 'R' && progression[3] == 'L') {
                    return PCRL;
                } else {
                    if (progression[0] == 'C' && progression[1] == 'P'
                            && progression[2] == 'R' && progression[3] == 'L') {
                        return CPRL;
                    } else {
                        return PROG_UNKNOWN;
                    }
                }
            }
        }
    }
}