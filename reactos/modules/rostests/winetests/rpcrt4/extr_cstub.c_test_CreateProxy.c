#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  Vtbl; } ;
struct TYPE_7__ {int /*<<< orphan*/  Vtbl; } ;
struct TYPE_6__ {int /*<<< orphan*/  Vtbl; } ;
struct TYPE_5__ {int /*<<< orphan*/  Vtbl; } ;
typedef  int /*<<< orphan*/  IPSFactoryBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  IID_if1 ; 
 int /*<<< orphan*/  IID_if2 ; 
 int /*<<< orphan*/  IID_if3 ; 
 int /*<<< orphan*/  IID_if4 ; 
 int /*<<< orphan*/  create_proxy_test (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__ if1_proxy_vtbl ; 
 TYPE_3__ if2_proxy_vtbl ; 
 TYPE_2__ if3_proxy_vtbl ; 
 TYPE_1__ if4_proxy_vtbl ; 

__attribute__((used)) static void test_CreateProxy( IPSFactoryBuffer *ppsf )
{
    create_proxy_test( ppsf, &IID_if1, if1_proxy_vtbl.Vtbl );
    create_proxy_test( ppsf, &IID_if2, if2_proxy_vtbl.Vtbl );
    create_proxy_test( ppsf, &IID_if3, if3_proxy_vtbl.Vtbl );
    create_proxy_test( ppsf, &IID_if4, if4_proxy_vtbl.Vtbl );
}