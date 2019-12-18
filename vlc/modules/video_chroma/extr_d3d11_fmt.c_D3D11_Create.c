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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_3__ {int /*<<< orphan*/  hdll; int /*<<< orphan*/  compiler_dll; void* OurD3DCompile; } ;
typedef  TYPE_1__ d3d11_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  Direct3D11LoadShaderLibrary () ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ ) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LoadLibrary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 

int D3D11_Create(vlc_object_t *obj, d3d11_handle_t *hd3d, bool with_shaders)
{
#if !VLC_WINSTORE_APP
    hd3d->hdll = LoadLibrary(TEXT("D3D11.DLL"));
    if (!hd3d->hdll)
    {
        msg_Warn(obj, "cannot load d3d11.dll, aborting");
        return VLC_EGENERIC;
    }

    if (with_shaders)
    {
        hd3d->compiler_dll = Direct3D11LoadShaderLibrary();
        if (!hd3d->compiler_dll) {
            msg_Err(obj, "cannot load d3dcompiler.dll, aborting");
            FreeLibrary(hd3d->hdll);
            return VLC_EGENERIC;
        }

        hd3d->OurD3DCompile = (void *)GetProcAddress(hd3d->compiler_dll, "D3DCompile");
        if (!hd3d->OurD3DCompile) {
            msg_Err(obj, "Cannot locate reference to D3DCompile in d3dcompiler DLL");
            FreeLibrary(hd3d->compiler_dll);
            FreeLibrary(hd3d->hdll);
            return VLC_EGENERIC;
        }
    }
#endif
    return VLC_SUCCESS;
}