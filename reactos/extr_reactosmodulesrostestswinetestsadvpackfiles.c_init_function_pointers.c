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

/* Variables and functions */
 scalar_t__ GetProcAddress (scalar_t__,char*) ; 
 scalar_t__ LoadLibraryA (char*) ; 
 scalar_t__ hAdvPack ; 
 void* pAddDelBackupEntry ; 
 void* pAdvInstallFile ; 
 void* pExtractFiles ; 
 void* pExtractFilesW ; 

__attribute__((used)) static void init_function_pointers(void)
{
    hAdvPack = LoadLibraryA("advpack.dll");

    if (hAdvPack)
    {
        pAddDelBackupEntry = (void *)GetProcAddress(hAdvPack, "AddDelBackupEntry");
        pExtractFiles = (void *)GetProcAddress(hAdvPack, "ExtractFiles");
        pExtractFilesW = (void *)GetProcAddress(hAdvPack, "ExtractFilesW");
        pAdvInstallFile = (void*)GetProcAddress(hAdvPack, "AdvInstallFile");
    }
}