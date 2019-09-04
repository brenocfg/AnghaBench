#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int iBand; int /*<<< orphan*/  flags; int /*<<< orphan*/  pt; } ;
typedef  int /*<<< orphan*/  REBAR_INFO ;
typedef  int LRESULT ;
typedef  TYPE_1__* LPRBHITTESTINFO ;

/* Variables and functions */
 int /*<<< orphan*/  REBAR_InternalHitTest (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static LRESULT
REBAR_HitTest (const REBAR_INFO *infoPtr, LPRBHITTESTINFO lprbht)
{
    if (!lprbht)
	return -1;

    REBAR_InternalHitTest (infoPtr, &lprbht->pt, &lprbht->flags, &lprbht->iBand);

    return lprbht->iBand;
}