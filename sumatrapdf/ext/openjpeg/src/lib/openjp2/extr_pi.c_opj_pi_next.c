#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int prg; } ;
struct TYPE_10__ {TYPE_1__ poc; } ;
typedef  TYPE_2__ opj_pi_iterator_t ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
#define  OPJ_CPRL 133 
 int /*<<< orphan*/  OPJ_FALSE ; 
#define  OPJ_LRCP 132 
#define  OPJ_PCRL 131 
#define  OPJ_PROG_UNKNOWN 130 
#define  OPJ_RLCP 129 
#define  OPJ_RPCL 128 
 int /*<<< orphan*/  opj_pi_next_cprl (TYPE_2__*) ; 
 int /*<<< orphan*/  opj_pi_next_lrcp (TYPE_2__*) ; 
 int /*<<< orphan*/  opj_pi_next_pcrl (TYPE_2__*) ; 
 int /*<<< orphan*/  opj_pi_next_rlcp (TYPE_2__*) ; 
 int /*<<< orphan*/  opj_pi_next_rpcl (TYPE_2__*) ; 

OPJ_BOOL opj_pi_next(opj_pi_iterator_t * pi)
{
    switch (pi->poc.prg) {
    case OPJ_LRCP:
        return opj_pi_next_lrcp(pi);
    case OPJ_RLCP:
        return opj_pi_next_rlcp(pi);
    case OPJ_RPCL:
        return opj_pi_next_rpcl(pi);
    case OPJ_PCRL:
        return opj_pi_next_pcrl(pi);
    case OPJ_CPRL:
        return opj_pi_next_cprl(pi);
    case OPJ_PROG_UNKNOWN:
        return OPJ_FALSE;
    }

    return OPJ_FALSE;
}