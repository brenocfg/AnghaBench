#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_3__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_4__ {TYPE_1__ FileOffset; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_2__* PROSSYM_KM_OWN_CONTEXT ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN
KdbpSeekSymFile(PVOID FileContext, ULONG_PTR Target)
{
    PROSSYM_KM_OWN_CONTEXT Context = (PROSSYM_KM_OWN_CONTEXT)FileContext;
    Context->FileOffset.QuadPart = Target;
    return TRUE;
}