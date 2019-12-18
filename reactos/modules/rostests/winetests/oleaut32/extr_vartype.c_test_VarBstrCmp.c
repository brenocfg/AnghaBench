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
typedef  int /*<<< orphan*/  sbchr00 ;
typedef  int /*<<< orphan*/  sbchr0 ;
typedef  int /*<<< orphan*/  sb2 ;
typedef  int /*<<< orphan*/  sb1 ;
typedef  char WCHAR ;
typedef  scalar_t__ LCID ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char const*) ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MAKELCID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NORM_IGNORECASE ; 
 int /*<<< orphan*/  SORT_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_US ; 
 int /*<<< orphan*/ * SysAllocString (char const*) ; 
 int /*<<< orphan*/ * SysAllocStringByteLen (char const*,int) ; 
 int /*<<< orphan*/ * SysAllocStringLen (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARBSTRCMP (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VARCMP_EQ ; 
 int /*<<< orphan*/  VARCMP_GT ; 
 int /*<<< orphan*/  VARCMP_LT ; 

__attribute__((used)) static void test_VarBstrCmp(void)
{
    LCID lcid;
    HRESULT hres;
    static const WCHAR sz[] = {'W','u','r','s','c','h','t','\0'};
    static const WCHAR szempty[] = {'\0'};
    static const WCHAR sz1[] = { 'a',0 };
    static const WCHAR sz2[] = { 'A',0 };
    static const WCHAR s1[] = { 'a',0 };
    static const WCHAR s2[] = { 'a',0,'b' };
    static const char sb1[] = {1,0,1};
    static const char sb2[] = {1,0,2};
    static const char sbchr0[] = {0,0};
    static const char sbchr00[] = {0,0,0};
    BSTR bstr, bstrempty, bstr2;

    lcid = MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT);
    bstr = SysAllocString(sz);
    bstrempty = SysAllocString(szempty);
    
    /* NULL handling. Yepp, MSDN is totally wrong here */
    VARBSTRCMP(NULL,NULL,0,VARCMP_EQ);
    VARBSTRCMP(bstr,NULL,0,VARCMP_GT);
    VARBSTRCMP(NULL,bstr,0,VARCMP_LT);

    /* NULL and empty string comparisons */
    VARBSTRCMP(bstrempty,NULL,0,VARCMP_EQ);
    VARBSTRCMP(NULL,bstrempty,0,VARCMP_EQ);

    SysFreeString(bstr);
    bstr = SysAllocString(sz1);

    bstr2 = SysAllocString(sz2);
    VARBSTRCMP(bstr,bstr2,0,VARCMP_LT);
    VARBSTRCMP(bstr,bstr2,NORM_IGNORECASE,VARCMP_EQ);
    SysFreeString(bstr2);
    /* These two strings are considered equal even though one is
     * NULL-terminated and the other not.
     */
    bstr2 = SysAllocStringLen(s1, ARRAY_SIZE(s1));
    VARBSTRCMP(bstr,bstr2,0,VARCMP_EQ);
    SysFreeString(bstr2);

    /* These two strings are not equal */
    bstr2 = SysAllocStringLen(s2, ARRAY_SIZE(s2));
    VARBSTRCMP(bstr,bstr2,0,VARCMP_LT);
    SysFreeString(bstr2);

    SysFreeString(bstr);

    bstr = SysAllocStringByteLen(sbchr0, sizeof(sbchr0));
    bstr2 = SysAllocStringByteLen(sbchr00, sizeof(sbchr00));
    VARBSTRCMP(bstr,bstrempty,0,VARCMP_GT);
    VARBSTRCMP(bstrempty,bstr,0,VARCMP_LT);
    VARBSTRCMP(bstr2,bstrempty,0,VARCMP_GT);
    VARBSTRCMP(bstr2,bstr,0,VARCMP_EQ);
    SysFreeString(bstr2);
    SysFreeString(bstr);

    /* When (LCID == 0) it should be a binary comparison
     * so these two strings could not match.
     */
    bstr = SysAllocStringByteLen(sb1, sizeof(sb1));
    bstr2 = SysAllocStringByteLen(sb2, sizeof(sb2));
    lcid = 0;
    VARBSTRCMP(bstr,bstr2,0,VARCMP_LT);
    SysFreeString(bstr2);
    SysFreeString(bstr);

    bstr = SysAllocStringByteLen(sbchr0, sizeof(sbchr0));
    bstr2 = SysAllocStringByteLen(sbchr00, sizeof(sbchr00));
    VARBSTRCMP(bstr,bstrempty,0,VARCMP_GT);
    VARBSTRCMP(bstrempty,bstr,0,VARCMP_LT);
    VARBSTRCMP(bstr2,bstrempty,0,VARCMP_GT);
    VARBSTRCMP(bstr2,bstr,0,VARCMP_GT);
    SysFreeString(bstr2);
    SysFreeString(bstr);
    SysFreeString(bstrempty);
}