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
struct TYPE_3__ {char* lpszClassName; } ;
typedef  TYPE_1__ WNDCLASSW ;
typedef  scalar_t__ ATOM ;

/* Variables and functions */
 char** ControlsList ; 
 scalar_t__ GetClassInfoW (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 scalar_t__ lstrcmpW (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  trace (char*,scalar_t__) ; 

void Test_ClassAtoms()
{
    ATOM atom;
    int i;
    WNDCLASSW cls;

    // Initialize starting Atom number.
    atom = GetClassInfoW(NULL, ControlsList[0], &cls);
    if (!atom)
    {
       skip( "No reference Atom\n" );
       return;
    }

    trace("First Control Class Atom 0x%x\n",atom);

    for (i = 0; i < 17; atom++ ,i++)
    {
        if (lstrcmpW(ControlsList[i],L"\0"))
        {
           ATOM test_atom = GetClassInfoW(NULL, ControlsList[i], &cls);
           // Skip unregistered Classes.
           if (test_atom)
           {
              ok(test_atom == atom, "%S class atom did not match %x:%x\n",ControlsList[i],test_atom,atom);
              ok(!lstrcmpW(cls.lpszClassName,ControlsList[i]),"GetClassName returned incorrect name\n");
           }
        }
    }
}