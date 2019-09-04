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
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateFileA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  PROG_FILES ; 
 int /*<<< orphan*/  WriteFile (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  append_str (char**,char*,...) ; 
 int /*<<< orphan*/  inf_file ; 

__attribute__((used)) static void create_inf_file(void)
{
    char data[1024];
    char *ptr = data;
    DWORD dwNumberOfBytesWritten;
    HANDLE hf = CreateFileA(inf_file, GENERIC_WRITE, 0, NULL,
                            CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    append_str(&ptr, "[Version]\n");
    append_str(&ptr, "Signature=\"$Chicago$\"\n");
    append_str(&ptr, "[CustInstDestSection]\n");
    append_str(&ptr, "49001=ProgramFilesDir\n");
    append_str(&ptr, "49010=DestA,1\n");
    append_str(&ptr, "49020=DestB\n");
    append_str(&ptr, "49030=DestC\n");
    append_str(&ptr, "[ProgramFilesDir]\n");
    append_str(&ptr, "HKLM,\"Software\\Microsoft\\Windows\\CurrentVersion\",");
    append_str(&ptr, "\"ProgramFilesDir\",,\"%%24%%\\%%LProgramF%%\"\n");
    append_str(&ptr, "[section]\n");
    append_str(&ptr, "NotACustomDestination=Version\n");
    append_str(&ptr, "CustomDestination=CustInstDestSection\n");
    append_str(&ptr, "[Options.NTx86]\n");
    append_str(&ptr, "49001=ProgramFilesDir\n");
    append_str(&ptr, "InstallDir=%%49001%%\\%%DefaultAppPath%%\n");
    append_str(&ptr, "Result1=%%49010%%\n");
    append_str(&ptr, "Result2=%%49020%%\n");
    append_str(&ptr, "Result3=%%49030%%\n");
    append_str(&ptr, "CustomHDestination=CustInstDestSection\n");
    append_str(&ptr, "[Strings]\n");
    append_str(&ptr, "DefaultAppPath=\"Application Name\"\n");
    append_str(&ptr, "LProgramF=\"%s\"\n", PROG_FILES);
    append_str(&ptr, "[DestA]\n");
    append_str(&ptr, "HKLM,\"Software\\Garbage\",\"ProgramFilesDir\",,'%%24%%\\%%LProgramF%%'\n");
    append_str(&ptr, "[DestB]\n");
    append_str(&ptr, "'HKLM','Software\\Microsoft\\Windows\\CurrentVersion',");
    append_str(&ptr, "'ProgramFilesDir',,\"%%24%%\"\n");
    append_str(&ptr, "[DestC]\n");
    append_str(&ptr, "HKLM,\"Software\\Garbage\",\"ProgramFilesDir\",,'%%24%%'\n");

    WriteFile(hf, data, ptr - data, &dwNumberOfBytesWritten, NULL);
    CloseHandle(hf);
}