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
typedef  int /*<<< orphan*/  LPDIDEVICEINSTANCEW ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ DI8DEVCLASS_POINTER ; 
 scalar_t__ DI8DEVTYPE_MOUSE ; 
 scalar_t__ DIDEVTYPE_MOUSE ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  fill_mouse_dideviceinstanceW (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static HRESULT mousedev_enum_deviceW(DWORD dwDevType, DWORD dwFlags, LPDIDEVICEINSTANCEW lpddi, DWORD version, int id)
{
    if (id != 0)
        return E_FAIL;

    if ((dwDevType == 0) ||
	((dwDevType == DIDEVTYPE_MOUSE) && (version < 0x0800)) ||
	(((dwDevType == DI8DEVCLASS_POINTER) || (dwDevType == DI8DEVTYPE_MOUSE)) && (version >= 0x0800))) {
	TRACE("Enumerating the mouse device\n");
	
	fill_mouse_dideviceinstanceW(lpddi, version);
	
	return S_OK;
    }
    
    return S_FALSE;
}