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
struct TYPE_4__ {int /*<<< orphan*/  dwRefCount; } ;
typedef  TYPE_1__* PTHEME_FILE ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 

HRESULT MSSTYLES_ReferenceTheme(PTHEME_FILE tf)
{
    tf->dwRefCount++;
    TRACE("Theme %p refcount: %d\n", tf, tf->dwRefCount);
    return S_OK;
}