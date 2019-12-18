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
typedef  void* LPVOID ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int /*<<< orphan*/  HRSRC ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FindResource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* LockResource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCE (int) ; 
 int /*<<< orphan*/  SizeofResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void* extract_rcdata (LPTSTR name, int type, DWORD* size)
{
    HRSRC rsrc;
    HGLOBAL hdl;
    LPVOID addr;
    
    if (!(rsrc = FindResource (NULL, name, MAKEINTRESOURCE(type))) ||
        !(*size = SizeofResource (0, rsrc)) ||
        !(hdl = LoadResource (0, rsrc)) ||
        !(addr = LockResource (hdl)))
        return NULL;
    return addr;
}