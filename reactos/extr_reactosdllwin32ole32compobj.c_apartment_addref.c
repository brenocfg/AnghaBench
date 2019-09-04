#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct apartment {int /*<<< orphan*/  oxid; int /*<<< orphan*/  refs; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ InterlockedIncrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wine_dbgstr_longlong (int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD apartment_addref(struct apartment *apt)
{
    DWORD refs = InterlockedIncrement(&apt->refs);
    TRACE("%s: before = %d\n", wine_dbgstr_longlong(apt->oxid), refs - 1);
    return refs;
}