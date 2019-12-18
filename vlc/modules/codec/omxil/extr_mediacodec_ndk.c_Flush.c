#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  p_codec; } ;
typedef  TYPE_2__ mc_api_sys ;
struct TYPE_8__ {TYPE_2__* p_sys; } ;
typedef  TYPE_3__ mc_api ;
struct TYPE_6__ {scalar_t__ (* flush ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {TYPE_1__ AMediaCodec; } ;

/* Variables and functions */
 scalar_t__ AMEDIA_OK ; 
 int MC_API_ERROR ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 TYPE_4__ syms ; 

__attribute__((used)) static int Flush(mc_api *api)
{
    mc_api_sys *p_sys = api->p_sys;

    if (syms.AMediaCodec.flush(p_sys->p_codec) == AMEDIA_OK)
        return 0;
    else
        return MC_API_ERROR;
}