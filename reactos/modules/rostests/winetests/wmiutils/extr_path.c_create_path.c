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
typedef  int /*<<< orphan*/  IWbemPath ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_WbemDefPath ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IWbemPath ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static IWbemPath *create_path(void)
{
    HRESULT hr;
    IWbemPath *path;

    hr = CoCreateInstance( &CLSID_WbemDefPath, NULL, CLSCTX_INPROC_SERVER, &IID_IWbemPath, (void **)&path );
    if (hr != S_OK)
    {
        win_skip( "can't create WbemDefPath instance, skipping tests\n" );
        return NULL;
    }
    return path;
}