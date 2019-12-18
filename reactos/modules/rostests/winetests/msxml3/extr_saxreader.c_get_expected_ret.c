#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ id; int /*<<< orphan*/  ret; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ CH_ENDTEST ; 
 TYPE_1__* expectCall ; 

__attribute__((used)) static HRESULT get_expected_ret(void)
{
    HRESULT hr = expectCall->ret;
    if (expectCall->id != CH_ENDTEST) expectCall++;
    return hr;
}