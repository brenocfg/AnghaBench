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
typedef  int /*<<< orphan*/  LPDATAOBJECT ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HGLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  DataObjectImpl_CreateFromHGlobal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GMEM_MOVEABLE ; 
 int /*<<< orphan*/  GlobalAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT DataObjectImpl_CreateText(LPCSTR text, LPDATAOBJECT *lplpdataobj)
{
    HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, strlen(text) + 1);
    strcpy(GlobalLock(h), text);
    GlobalUnlock(h);
    return DataObjectImpl_CreateFromHGlobal(h, lplpdataobj);
}