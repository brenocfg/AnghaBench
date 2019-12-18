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
struct TYPE_3__ {int /*<<< orphan*/ * fptr_MFCreateAlignedMemoryBuffer; int /*<<< orphan*/ * fptr_MFCreateMemoryBuffer; int /*<<< orphan*/ * fptr_MFCreateSample; int /*<<< orphan*/ * fptr_MFTEnumEx; int /*<<< orphan*/  mfplat_dll; } ;
typedef  TYPE_1__ MFHandle ;

/* Variables and functions */
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LoadLibrary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MFCreateAlignedMemoryBuffer ; 
 int /*<<< orphan*/  MFCreateMemoryBuffer ; 
 int /*<<< orphan*/  MFCreateSample ; 
 int /*<<< orphan*/  MFTEnumEx ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static int LoadMFTLibrary(MFHandle *mf)
{
#if _WIN32_WINNT < _WIN32_WINNT_WIN7 || VLC_WINSTORE_APP || __MINGW64_VERSION_MAJOR < 6
    mf->mfplat_dll = LoadLibrary(TEXT("mfplat.dll"));
    if (!mf->mfplat_dll)
        return VLC_EGENERIC;

    mf->fptr_MFTEnumEx = (void*)GetProcAddress(mf->mfplat_dll, "MFTEnumEx");
    mf->fptr_MFCreateSample = (void*)GetProcAddress(mf->mfplat_dll, "MFCreateSample");
    mf->fptr_MFCreateMemoryBuffer = (void*)GetProcAddress(mf->mfplat_dll, "MFCreateMemoryBuffer");
    mf->fptr_MFCreateAlignedMemoryBuffer = (void*)GetProcAddress(mf->mfplat_dll, "MFCreateAlignedMemoryBuffer");
    if (!mf->fptr_MFTEnumEx || !mf->fptr_MFCreateSample || !mf->fptr_MFCreateMemoryBuffer || !mf->fptr_MFCreateAlignedMemoryBuffer)
        return VLC_EGENERIC;
#else
    mf->fptr_MFTEnumEx = &MFTEnumEx;
    mf->fptr_MFCreateSample = &MFCreateSample;
    mf->fptr_MFCreateMemoryBuffer = &MFCreateMemoryBuffer;
    mf->fptr_MFCreateAlignedMemoryBuffer = &MFCreateAlignedMemoryBuffer;
#endif

    return VLC_SUCCESS;
}