#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_4__ {int /*<<< orphan*/  refCount; } ;
typedef  TYPE_1__ InternetShortcut ;

/* Variables and functions */
 int /*<<< orphan*/  InterlockedIncrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 

__attribute__((used)) static ULONG Unknown_AddRef(InternetShortcut *This)
{
    TRACE("(%p)\n", This);
    return InterlockedIncrement(&This->refCount);
}