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
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  PSTIW ;
typedef  int /*<<< orphan*/  PSTIA ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS_E_NOAGGREGATION ; 
 int /*<<< orphan*/  E_NOINTERFACE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  IID_IStillImageA ; 
 int /*<<< orphan*/  IID_IStillImageW ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsEqualIID (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int STI_VERSION_FLAG_UNICODE ; 
 int STI_VERSION_REAL ; 
 int /*<<< orphan*/  StiCreateInstanceA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StiCreateInstanceW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT sti_create( REFIID riid, IUnknown *pUnkOuter, LPVOID *ppObj )
{
    if (pUnkOuter != NULL && !IsEqualIID(riid, &IID_IUnknown))
        return CLASS_E_NOAGGREGATION;

    if (IsEqualGUID(riid, &IID_IUnknown))
        return StiCreateInstanceW(GetCurrentProcess(), STI_VERSION_REAL | STI_VERSION_FLAG_UNICODE, (PSTIW*) ppObj, pUnkOuter);
    else if (IsEqualGUID(riid, &IID_IStillImageW))
        return StiCreateInstanceW(GetCurrentProcess(), STI_VERSION_REAL | STI_VERSION_FLAG_UNICODE, (PSTIW*) ppObj, NULL);
    else if (IsEqualGUID(riid, &IID_IStillImageA))
        return StiCreateInstanceA(GetCurrentProcess(), STI_VERSION_REAL, (PSTIA*) ppObj, NULL);
    else
    {
        FIXME("no interface %s\n", debugstr_guid(riid));
        return E_NOINTERFACE;
    }
}