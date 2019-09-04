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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_BEGIN ; 
 int /*<<< orphan*/  ReadFile (int /*<<< orphan*/ ,char*,int,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetFilePointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *read_file( HANDLE file )
{
    static char buffer[128];
    DWORD ret;
    SetFilePointer( file, 0, NULL, FILE_BEGIN );
    if (!ReadFile( file, buffer, sizeof(buffer) - 1, &ret, NULL)) ret = 0;
    buffer[ret] = 0;
    return buffer;
}