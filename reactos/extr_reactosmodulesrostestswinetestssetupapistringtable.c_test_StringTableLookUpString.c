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
typedef  int /*<<< orphan*/ * HSTRING_TABLE ;
typedef  unsigned int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ST_CASE_SENSITIVE_COMPARE ; 
 int /*<<< orphan*/  String ; 
 int /*<<< orphan*/  foo ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 unsigned int pStringTableAddString (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pStringTableDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pStringTableDuplicate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pStringTableInitialize () ; 
 unsigned int pStringTableLookUpString (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string ; 

__attribute__((used)) static void test_StringTableLookUpString(void)
{   
    DWORD retval, retval2, hstring, hString, hfoo;
    HSTRING_TABLE table, table2;

    table = pStringTableInitialize();
    ok(table != NULL,"failed to initialize string table\n");

    hstring = pStringTableAddString(table, string, 0);
    ok(hstring != ~0u, "failed to add 'string' to string table\n");

    hString = pStringTableAddString(table, String, 0);
    ok(hString != ~0u,"failed to add 'String' to string table\n");

    hfoo = pStringTableAddString(table, foo, 0);
    ok(hfoo != ~0u, "failed to add 'foo' to string table\n");

    table2 = pStringTableDuplicate(table);
    ok(table2 != NULL, "Failed to duplicate String Table\n");

    /* case insensitive */
    retval=pStringTableLookUpString(table,string,0);
    ok(retval!=-1,"Failed find string in String Table 1\n");
    ok(retval==hstring,
        "Lookup for string (%x) does not match previous handle (%x) in String Table 1\n",
        retval, hstring);    

    retval=pStringTableLookUpString(table2,string,0);
    ok(retval!=-1,"Failed find string in String Table 2\n");
    
    retval=pStringTableLookUpString(table,String,0);
    ok(retval!=-1,"Failed find String in String Table 1\n");

    retval=pStringTableLookUpString(table2,String,0);
    ok(retval!=-1,"Failed find String in String Table 2\n");    
    
    retval=pStringTableLookUpString(table,foo,0);
    ok(retval!=-1,"Failed find foo in String Table 1\n");    
    ok(retval==hfoo,
        "Lookup for foo (%x) does not match previous handle (%x) in String Table 1\n",
        retval, hfoo);        
    
    retval=pStringTableLookUpString(table2,foo,0);
    ok(retval!=-1,"Failed find foo in String Table 2\n");    
    
    /* case sensitive */
    retval=pStringTableLookUpString(table,string,ST_CASE_SENSITIVE_COMPARE);
    retval2=pStringTableLookUpString(table,String,ST_CASE_SENSITIVE_COMPARE);    
    ok(retval!=retval2,"Lookup of string equals String in Table 1\n");
    ok(retval==hString,
        "Lookup for String (%x) does not match previous handle (%x) in String Table 1\n",
        retval, hString);

    pStringTableDestroy(table);
    pStringTableDestroy(table2);
}