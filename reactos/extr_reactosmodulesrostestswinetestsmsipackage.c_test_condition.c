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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  scalar_t__ MSICONDITION ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_INSTALL_PACKAGE_REJECTED ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ MSICONDITION_ERROR ; 
 scalar_t__ MSICONDITION_FALSE ; 
 scalar_t__ MSICONDITION_NONE ; 
 scalar_t__ MSICONDITION_TRUE ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiEvaluateConditionA (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ MsiEvaluateConditionW (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  MsiSetPropertyA (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  create_package_db () ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ package_from_db (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_condition(void)
{
    static const WCHAR cond1[] = {'\"','a',0x30a,'\"','<','\"',0xe5,'\"',0};
    static const WCHAR cond2[] = {'\"','a',0x30a,'\"','>','\"',0xe5,'\"',0};
    static const WCHAR cond3[] = {'\"','a',0x30a,'\"','<','>','\"',0xe5,'\"',0};
    static const WCHAR cond4[] = {'\"','a',0x30a,'\"','=','\"',0xe5,'\"',0};
    MSICONDITION r;
    MSIHANDLE hpkg;

    r = package_from_db(create_package_db(), &hpkg);
    if (r == ERROR_INSTALL_PACKAGE_REJECTED)
    {
        skip("Not enough rights to perform tests\n");
        DeleteFileA(msifile);
        return;
    }
    ok( r == ERROR_SUCCESS, "failed to create package %u\n", r);

    r = MsiEvaluateConditionA(0, NULL);
    ok( r == MSICONDITION_ERROR, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, NULL);
    ok( r == MSICONDITION_NONE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "");
    ok( r == MSICONDITION_NONE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "1");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "0");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "-1");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "0 = 0");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "0 <> 0");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "0 = 1");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "0 > 1");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "0 ~> 1");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "1 > 1");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "1 ~> 1");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "0 >= 1");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "0 ~>= 1");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "1 >= 1");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "1 ~>= 1");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "0 < 1");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "0 ~< 1");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "1 < 1");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "1 ~< 1");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "0 <= 1");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "0 ~<= 1");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "1 <= 1");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "1 ~<= 1");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "0 >=");
    ok( r == MSICONDITION_ERROR, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, " ");
    ok( r == MSICONDITION_NONE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "LicView <> \"1\"");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "LicView <> \"0\"");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "LicView <> LicView");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "not 0");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "not LicView");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "\"Testing\" ~<< \"Testing\"");
    ok (r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "LicView ~<< \"Testing\"");
    ok (r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "Not LicView ~<< \"Testing\"");
    ok (r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "not \"A\"");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "~not \"A\"");
    ok( r == MSICONDITION_ERROR, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "\"0\"");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "1 and 2");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "not 0 and 3");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "not 0 and 0");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "not 0 or 1");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "(0)");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "(((((1))))))");
    ok( r == MSICONDITION_ERROR, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "(((((1)))))");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, " \"A\" < \"B\" ");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, " \"A\" > \"B\" ");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, " \"1\" > \"12\" ");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, " \"100\" < \"21\" ");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "0 < > 0");
    ok( r == MSICONDITION_ERROR, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "(1<<1) == 2");
    ok( r == MSICONDITION_ERROR, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, " \"A\" = \"a\" ");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, " \"A\" ~ = \"a\" ");
    ok( r == MSICONDITION_ERROR, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, " \"A\" ~= \"a\" ");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, " \"A\" ~= 1 ");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, " \"A\" = 1 ");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, " 1 ~= 1 ");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, " 1 ~= \"1\" ");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, " 1 = \"1\" ");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, " 0 = \"1\" ");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, " 0 < \"100\" ");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, " 100 > \"0\" ");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "1 XOR 1");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "1 IMP 1");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "1 IMP 0");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "0 IMP 0");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "0 EQV 0");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "0 EQV 1");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "1 IMP 1 OR 0");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "1 IMPL 1");
    ok( r == MSICONDITION_ERROR, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "\"ASFD\" >< \"S\" ");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "\"ASFD\" ~>< \"s\" ");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "\"ASFD\" ~>< \"\" ");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "\"ASFD\" ~>< \"sss\" ");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "mm", "5" );

    r = MsiEvaluateConditionA(hpkg, "mm = 5");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "mm < 6");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "mm <= 5");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "mm > 4");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "mm < 12");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "mm = \"5\"");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "0 = \"\"");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "0 AND \"\"");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "1 AND \"\"");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "1 AND \"1\"");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "3 >< 1");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "3 >< 4");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "NOT 0 AND 0");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "NOT 0 AND 1");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "NOT 1 OR 0");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "0 AND 1 OR 1");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "0 AND 0 OR 1");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "NOT 0 AND 1 OR 0");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "_1 = _1");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "( 1 AND 1 ) = 2");
    ok( r == MSICONDITION_ERROR, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "NOT ( 1 AND 1 )");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "NOT A AND (BBBBBBBBBB=2 OR CCC=1) AND Ddddddddd");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "Installed<>\"\"");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "NOT 1 AND 0");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "bandalmael=0");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "bandalmael<>0");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "bandalmael<0");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "bandalmael>0");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "bandalmael>=0");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "bandalmael<=0");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    r = MsiEvaluateConditionA(hpkg, "bandalmael~<>0");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "bandalmael", "0" );
    r = MsiEvaluateConditionA(hpkg, "bandalmael=0");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "bandalmael", "" );
    r = MsiEvaluateConditionA(hpkg, "bandalmael=0");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "bandalmael", "asdf" );
    r = MsiEvaluateConditionA(hpkg, "bandalmael=0");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "bandalmael", "0asdf" );
    r = MsiEvaluateConditionA(hpkg, "bandalmael=0");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "bandalmael", "0 " );
    r = MsiEvaluateConditionA(hpkg, "bandalmael=0");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "bandalmael", "-0" );
    r = MsiEvaluateConditionA(hpkg, "bandalmael=0");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "bandalmael", "0000000000000" );
    r = MsiEvaluateConditionA(hpkg, "bandalmael=0");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "bandalmael", "--0" );
    r = MsiEvaluateConditionA(hpkg, "bandalmael=0");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "bandalmael", "0x00" );
    r = MsiEvaluateConditionA(hpkg, "bandalmael=0");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "bandalmael", "-" );
    r = MsiEvaluateConditionA(hpkg, "bandalmael=0");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "bandalmael", "+0" );
    r = MsiEvaluateConditionA(hpkg, "bandalmael=0");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "bandalmael", "0.0" );
    r = MsiEvaluateConditionA(hpkg, "bandalmael=0");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");
    r = MsiEvaluateConditionA(hpkg, "bandalmael<>0");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "hi");
    MsiSetPropertyA(hpkg, "two", "hithere");
    r = MsiEvaluateConditionA(hpkg, "one >< two");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "hithere");
    MsiSetPropertyA(hpkg, "two", "hi");
    r = MsiEvaluateConditionA(hpkg, "one >< two");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "hello");
    MsiSetPropertyA(hpkg, "two", "hi");
    r = MsiEvaluateConditionA(hpkg, "one >< two");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "hellohithere");
    MsiSetPropertyA(hpkg, "two", "hi");
    r = MsiEvaluateConditionA(hpkg, "one >< two");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "");
    MsiSetPropertyA(hpkg, "two", "hi");
    r = MsiEvaluateConditionA(hpkg, "one >< two");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "hi");
    MsiSetPropertyA(hpkg, "two", "");
    r = MsiEvaluateConditionA(hpkg, "one >< two");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "");
    MsiSetPropertyA(hpkg, "two", "");
    r = MsiEvaluateConditionA(hpkg, "one >< two");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "1234");
    MsiSetPropertyA(hpkg, "two", "1");
    r = MsiEvaluateConditionA(hpkg, "one >< two");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "one 1234");
    MsiSetPropertyA(hpkg, "two", "1");
    r = MsiEvaluateConditionA(hpkg, "one >< two");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "hithere");
    MsiSetPropertyA(hpkg, "two", "hi");
    r = MsiEvaluateConditionA(hpkg, "one << two");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "hi");
    MsiSetPropertyA(hpkg, "two", "hithere");
    r = MsiEvaluateConditionA(hpkg, "one << two");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "hi");
    MsiSetPropertyA(hpkg, "two", "hi");
    r = MsiEvaluateConditionA(hpkg, "one << two");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "abcdhithere");
    MsiSetPropertyA(hpkg, "two", "hi");
    r = MsiEvaluateConditionA(hpkg, "one << two");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "");
    MsiSetPropertyA(hpkg, "two", "hi");
    r = MsiEvaluateConditionA(hpkg, "one << two");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "hithere");
    MsiSetPropertyA(hpkg, "two", "");
    r = MsiEvaluateConditionA(hpkg, "one << two");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "");
    MsiSetPropertyA(hpkg, "two", "");
    r = MsiEvaluateConditionA(hpkg, "one << two");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "1234");
    MsiSetPropertyA(hpkg, "two", "1");
    r = MsiEvaluateConditionA(hpkg, "one << two");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "1234 one");
    MsiSetPropertyA(hpkg, "two", "1");
    r = MsiEvaluateConditionA(hpkg, "one << two");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "hithere");
    MsiSetPropertyA(hpkg, "two", "there");
    r = MsiEvaluateConditionA(hpkg, "one >> two");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "hithere");
    MsiSetPropertyA(hpkg, "two", "hi");
    r = MsiEvaluateConditionA(hpkg, "one >> two");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "there");
    MsiSetPropertyA(hpkg, "two", "hithere");
    r = MsiEvaluateConditionA(hpkg, "one >> two");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "there");
    MsiSetPropertyA(hpkg, "two", "there");
    r = MsiEvaluateConditionA(hpkg, "one >> two");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "abcdhithere");
    MsiSetPropertyA(hpkg, "two", "hi");
    r = MsiEvaluateConditionA(hpkg, "one >> two");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "");
    MsiSetPropertyA(hpkg, "two", "there");
    r = MsiEvaluateConditionA(hpkg, "one >> two");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "there");
    MsiSetPropertyA(hpkg, "two", "");
    r = MsiEvaluateConditionA(hpkg, "one >> two");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "");
    MsiSetPropertyA(hpkg, "two", "");
    r = MsiEvaluateConditionA(hpkg, "one >> two");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "1234");
    MsiSetPropertyA(hpkg, "two", "4");
    r = MsiEvaluateConditionA(hpkg, "one >> two");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "one", "one 1234");
    MsiSetPropertyA(hpkg, "two", "4");
    r = MsiEvaluateConditionA(hpkg, "one >> two");
    ok( r == MSICONDITION_TRUE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "MsiNetAssemblySupport", NULL);  /* make sure it's empty */

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"1.1.4322\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport > \"1.1.4322\"");
    ok( r == MSICONDITION_FALSE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport >= \"1.1.4322\"");
    ok( r == MSICONDITION_FALSE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport <= \"1.1.4322\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport <> \"1.1.4322\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport ~< \"1.1.4322\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"abcd\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"a1.1.4322\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"1.1.4322a\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"0000001.1.4322\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"1.1.4322.1\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"1.1.4322.1.1\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "\"2\" < \"1.1");
    ok( r == MSICONDITION_ERROR, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "\"2\" < \"1.1\"");
    ok( r == MSICONDITION_FALSE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "\"2\" < \"12.1\"");
    ok( r == MSICONDITION_FALSE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "\"02.1\" < \"2.11\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "\"02.1.1\" < \"2.1\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"1.1\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"1\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"0\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"-1\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"a\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"!\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"!\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"/\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \" \"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"azAZ_\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"a[a]\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"a[a]a\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"[a]\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"[a]a\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"{a}\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"{a\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"[a\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"a{\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"a]\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"A\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    MsiSetPropertyA(hpkg, "MsiNetAssemblySupport", "1.1.4322");
    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"1.1.4322\"");
    ok( r == MSICONDITION_FALSE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"1.1.14322\"");
    ok( r == MSICONDITION_FALSE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"1.1.5\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"1.1\"");
    ok( r == MSICONDITION_FALSE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "MsiNetAssemblySupport < \"1\"");
    ok( r == MSICONDITION_FALSE, "wrong return val (%d)\n", r);

    MsiSetPropertyA(hpkg, "one", "1");
    r = MsiEvaluateConditionA(hpkg, "one < \"1\"");
    ok( r == MSICONDITION_FALSE, "wrong return val\n");

    MsiSetPropertyA(hpkg, "X", "5.0");

    r = MsiEvaluateConditionA(hpkg, "X != \"\"");
    ok( r == MSICONDITION_ERROR, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "X =\"5.0\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "X =\"5.1\"");
    ok( r == MSICONDITION_FALSE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "X =\"6.0\"");
    ok( r == MSICONDITION_FALSE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "X =\"5.0\" or X =\"5.1\" or X =\"6.0\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "(X =\"5.0\" or X =\"5.1\" or X =\"6.0\")");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "X !=\"\" and (X =\"5.0\" or X =\"5.1\" or X =\"6.0\")");
    ok( r == MSICONDITION_ERROR, "wrong return val (%d)\n", r);

    /* feature doesn't exist */
    r = MsiEvaluateConditionA(hpkg, "&nofeature");
    ok( r == MSICONDITION_FALSE, "wrong return val (%d)\n", r);
    r = MsiEvaluateConditionA(hpkg, "&nofeature=\"\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);
    r = MsiEvaluateConditionA(hpkg, "!nofeature=\"\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);
    MsiEvaluateConditionA(hpkg, "$nocomponent=\"\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);
    MsiEvaluateConditionA(hpkg, "?nocomponent=\"\"");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    MsiSetPropertyA(hpkg, "A", "2");
    MsiSetPropertyA(hpkg, "X", "50");

    r = MsiEvaluateConditionA(hpkg, "2 <= X");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "A <= X");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "A <= 50");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    MsiSetPropertyA(hpkg, "X", "50val");

    r = MsiEvaluateConditionA(hpkg, "2 <= X");
    ok( r == MSICONDITION_FALSE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "A <= X");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    MsiSetPropertyA(hpkg, "A", "7");
    MsiSetPropertyA(hpkg, "X", "50");

    r = MsiEvaluateConditionA(hpkg, "7 <= X");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "A <= X");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "A <= 50");
    ok( r == MSICONDITION_TRUE, "wrong return val (%d)\n", r);

    MsiSetPropertyA(hpkg, "X", "50val");

    r = MsiEvaluateConditionA(hpkg, "2 <= X");
    ok( r == MSICONDITION_FALSE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionA(hpkg, "A <= X");
    ok( r == MSICONDITION_FALSE, "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionW(hpkg, cond1);
    ok( r == MSICONDITION_TRUE || broken(r == MSICONDITION_FALSE),
        "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionW(hpkg, cond2);
    ok( r == MSICONDITION_FALSE || broken(r == MSICONDITION_TRUE),
        "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionW(hpkg, cond3);
    ok( r == MSICONDITION_TRUE || broken(r == MSICONDITION_FALSE),
        "wrong return val (%d)\n", r);

    r = MsiEvaluateConditionW(hpkg, cond4);
    ok( r == MSICONDITION_FALSE || broken(r == MSICONDITION_TRUE),
        "wrong return val (%d)\n", r);

    MsiCloseHandle( hpkg );
    DeleteFileA(msifile);
}