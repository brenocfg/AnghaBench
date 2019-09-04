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
typedef  int /*<<< orphan*/  new_val ;
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  IMMDevice ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  ERole ;
typedef  int /*<<< orphan*/  EDataFlow ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (scalar_t__*) ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IMMDevice_GetId (int /*<<< orphan*/ *,scalar_t__**) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,scalar_t__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  lstrcmpW (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  notify_clients (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static BOOL notify_if_changed(EDataFlow flow, ERole role, HKEY key,
                              const WCHAR *val_name, WCHAR *old_val, IMMDevice *def_dev)
{
    WCHAR new_val[64], *id;
    DWORD size;
    HRESULT hr;

    size = sizeof(new_val);
    if(RegQueryValueExW(key, val_name, 0, NULL,
                (BYTE*)new_val, &size) != ERROR_SUCCESS){
        if(old_val[0] != 0){
            /* set by user -> system default */
            if(def_dev){
                hr = IMMDevice_GetId(def_dev, &id);
                if(FAILED(hr)){
                    ERR("GetId failed: %08x\n", hr);
                    return FALSE;
                }
            }else
                id = NULL;

            notify_clients(flow, role, id);
            old_val[0] = 0;
            CoTaskMemFree(id);

            return TRUE;
        }

        /* system default -> system default, noop */
        return FALSE;
    }

    if(!lstrcmpW(old_val, new_val)){
        /* set by user -> same value */
        return FALSE;
    }

    if(new_val[0] != 0){
        /* set by user -> different value */
        notify_clients(flow, role, new_val);
        memcpy(old_val, new_val, sizeof(new_val));
        return TRUE;
    }

    /* set by user -> system default */
    if(def_dev){
        hr = IMMDevice_GetId(def_dev, &id);
        if(FAILED(hr)){
            ERR("GetId failed: %08x\n", hr);
            return FALSE;
        }
    }else
        id = NULL;

    notify_clients(flow, role, id);
    old_val[0] = 0;
    CoTaskMemFree(id);

    return TRUE;
}