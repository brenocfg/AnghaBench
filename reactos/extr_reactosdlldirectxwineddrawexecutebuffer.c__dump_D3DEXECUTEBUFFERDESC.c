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
struct TYPE_3__ {int /*<<< orphan*/  lpData; int /*<<< orphan*/  dwBufferSize; int /*<<< orphan*/  dwCaps; int /*<<< orphan*/  dwFlags; int /*<<< orphan*/  dwSize; } ;
typedef  TYPE_1__ D3DEXECUTEBUFFERDESC ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _dump_D3DEXECUTEBUFFERDESC(const D3DEXECUTEBUFFERDESC *lpDesc) {
    TRACE("dwSize       : %d\n", lpDesc->dwSize);
    TRACE("dwFlags      : %x\n", lpDesc->dwFlags);
    TRACE("dwCaps       : %x\n", lpDesc->dwCaps);
    TRACE("dwBufferSize : %d\n", lpDesc->dwBufferSize);
    TRACE("lpData       : %p\n", lpDesc->lpData);
}