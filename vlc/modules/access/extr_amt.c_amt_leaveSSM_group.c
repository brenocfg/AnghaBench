#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_14__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_11__ {int /*<<< orphan*/  s_addr; } ;
struct ip_mreq_source {TYPE_7__ imr_interface; TYPE_4__ imr_sourceaddr; TYPE_1__ imr_multiaddr; } ;
struct TYPE_18__ {TYPE_9__* p_sys; } ;
typedef  TYPE_8__ stream_t ;
typedef  int /*<<< orphan*/  imr ;
struct TYPE_15__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_16__ {TYPE_5__ sin_addr; } ;
struct TYPE_12__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_13__ {TYPE_2__ sin_addr; } ;
struct TYPE_19__ {int /*<<< orphan*/  sAMT; TYPE_6__ mcastSrcAddr; TYPE_3__ mcastGroupAddr; } ;
typedef  TYPE_9__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IP_DROP_SOURCE_MEMBERSHIP ; 
 int setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int amt_leaveSSM_group( stream_t *p_access )
{
    struct ip_mreq_source imr;
    access_sys_t *sys = p_access->p_sys;

    imr.imr_multiaddr.s_addr = sys->mcastGroupAddr.sin_addr.s_addr;
    imr.imr_sourceaddr.s_addr = sys->mcastSrcAddr.sin_addr.s_addr;
    imr.imr_interface.s_addr = INADDR_ANY;

    return setsockopt( sys->sAMT, IPPROTO_IP, IP_DROP_SOURCE_MEMBERSHIP, (char *)&imr, sizeof(imr) );
}