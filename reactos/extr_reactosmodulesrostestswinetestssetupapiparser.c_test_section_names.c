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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  error; int /*<<< orphan*/  section; int /*<<< orphan*/  data; } ;
typedef  int LONG ;
typedef  scalar_t__ HINF ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  SetupCloseInfFile (scalar_t__) ; 
 int SetupGetLineCountA (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,unsigned int,int /*<<< orphan*/ ,...) ; 
 TYPE_1__* section_names ; 
 scalar_t__ test_file_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace (char*,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_section_names(void)
{
    unsigned int i;
    UINT err_line;
    HINF hinf;
    DWORD err;
    LONG ret;

    for (i = 0; i < ARRAY_SIZE(section_names); i++)
    {
        SetLastError( 0xdeadbeef );
        hinf = test_file_contents( section_names[i].data, &err_line );
        ok( hinf != INVALID_HANDLE_VALUE, "line %u: open failed err %u\n", i, GetLastError() );
        if (hinf == INVALID_HANDLE_VALUE) continue;

        ret = SetupGetLineCountA( hinf, section_names[i].section );
        err = GetLastError();
        trace( "hinf=%p ret=%d err=0x%x\n", hinf, ret, err );
        if (ret != -1)
        {
            ok( !section_names[i].error, "line %u: section name %s found\n",
                i, section_names[i].section );
            ok( !err, "line %u: bad error code %u\n", i, err );
        }
        else
        {
            ok( section_names[i].error, "line %u: section name %s not found\n",
                i, section_names[i].section );
            ok( err == section_names[i].error, "line %u: bad error %u/%u\n",
                i, err, section_names[i].error );
        }
        SetupCloseInfFile( hinf );
    }
}