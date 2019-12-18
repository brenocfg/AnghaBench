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
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ST_CASE_SENSITIVE_COMPARE ; 
 int /*<<< orphan*/  String ; 
 int /*<<< orphan*/  foo ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pStringTableAddString (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pStringTableDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pStringTableInitialize () ; 
 int /*<<< orphan*/  string ; 

__attribute__((used)) static void test_StringTableAddString(void)
{
    DWORD retval, hstring, hString, hfoo;
    HSTRING_TABLE table;

    table = pStringTableInitialize();
    ok(table != NULL, "failed to initialize string table\n");

    /* case insensitive */
    hstring=pStringTableAddString(table,string,0);
    ok(hstring!=-1,"Failed to add string to String Table\n");

    retval=pStringTableAddString(table,String,0);
    ok(retval!=-1,"Failed to add String to String Table\n");    
    ok(hstring==retval,"string handle %x != String handle %x in String Table\n", hstring, retval);        
    
    hfoo=pStringTableAddString(table,foo,0);
    ok(hfoo!=-1,"Failed to add foo to String Table\n");        
    ok(hfoo!=hstring,"foo and string share the same ID %x in String Table\n", hfoo);            
    
    /* case sensitive */    
    hString=pStringTableAddString(table,String,ST_CASE_SENSITIVE_COMPARE);
    ok(hstring!=hString,"String handle and string share same ID %x in Table\n", hstring);        

    pStringTableDestroy(table);
}