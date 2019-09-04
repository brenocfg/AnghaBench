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
typedef  int /*<<< orphan*/  HMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 void* pStringTableAddString ; 
 void* pStringTableAddStringEx ; 
 void* pStringTableDestroy ; 
 void* pStringTableDuplicate ; 
 void* pStringTableGetExtraData ; 
 void* pStringTableInitialize ; 
 void* pStringTableInitializeEx ; 
 void* pStringTableLookUpString ; 
 void* pStringTableLookUpStringEx ; 
 void* pStringTableStringFromId ; 

__attribute__((used)) static void load_it_up(void)
{
    HMODULE hdll = GetModuleHandleA("setupapi.dll");

#define X(f) if (!(p##f = (void*)GetProcAddress(hdll, #f))) \
                 p##f = (void*)GetProcAddress(hdll, "pSetup"#f);
    X(StringTableInitialize);
    X(StringTableInitializeEx);
    X(StringTableAddString);
    X(StringTableAddStringEx);
    X(StringTableDuplicate);
    X(StringTableDestroy);
    X(StringTableLookUpString);
    X(StringTableLookUpStringEx);
    X(StringTableStringFromId);
    X(StringTableGetExtraData);
#undef X
}