#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  cbData; scalar_t__ pbData; } ;
struct TYPE_11__ {int /*<<< orphan*/  szPrompt; struct TYPE_11__* hwndApp; struct TYPE_11__* dwPromptFlags; struct TYPE_11__* cbSize; } ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  TYPE_1__* DWORD ;
typedef  TYPE_2__ DATA_BLOB ;
typedef  TYPE_1__ CRYPTPROTECT_PROMPTSTRUCT ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,...) ; 
 int /*<<< orphan*/  TRACE_DATA_BLOB (TYPE_2__ const*) ; 
 TYPE_1__* debugstr_an (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* debugstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
report(const DATA_BLOB* pDataIn, const DATA_BLOB* pOptionalEntropy,
       CRYPTPROTECT_PROMPTSTRUCT* pPromptStruct, DWORD dwFlags)
{
    TRACE("pPromptStruct: %p\n", pPromptStruct);
    if (pPromptStruct)
    {
        TRACE("  cbSize: 0x%x\n", pPromptStruct->cbSize);
        TRACE("  dwPromptFlags: 0x%x\n", pPromptStruct->dwPromptFlags);
        TRACE("  hwndApp: %p\n", pPromptStruct->hwndApp);
        TRACE("  szPrompt: %p %s\n",
              pPromptStruct->szPrompt,
              pPromptStruct->szPrompt ? debugstr_w(pPromptStruct->szPrompt)
              : "");
    }
    TRACE("dwFlags: 0x%04x\n", dwFlags);
    TRACE_DATA_BLOB(pDataIn);
    if (pOptionalEntropy)
    {
        TRACE_DATA_BLOB(pOptionalEntropy);
        TRACE("  %s\n",debugstr_an((LPCSTR)pOptionalEntropy->pbData,pOptionalEntropy->cbData));
    }

}