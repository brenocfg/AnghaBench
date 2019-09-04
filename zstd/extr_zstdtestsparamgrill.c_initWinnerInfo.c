#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cSpeed; int dSpeed; size_t cMem; size_t cSize; } ;
struct TYPE_5__ {int /*<<< orphan*/  params; TYPE_1__ result; } ;
typedef  TYPE_2__ winnerInfo_t ;
typedef  int /*<<< orphan*/  paramValues_t ;

/* Variables and functions */

__attribute__((used)) static winnerInfo_t initWinnerInfo(const paramValues_t p)
{
    winnerInfo_t w1;
    w1.result.cSpeed = 0.;
    w1.result.dSpeed = 0.;
    w1.result.cMem = (size_t)-1;
    w1.result.cSize = (size_t)-1;
    w1.params = p;
    return w1;
}