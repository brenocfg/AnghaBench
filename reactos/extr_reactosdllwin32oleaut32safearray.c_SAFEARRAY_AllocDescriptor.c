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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  SAFEARRAY ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int SAFEARRAY_HIDDEN_SIZE ; 
 char* SAFEARRAY_Malloc (int) ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT SAFEARRAY_AllocDescriptor(ULONG ulSize, SAFEARRAY **ppsaOut)
{
  char *ptr = SAFEARRAY_Malloc(ulSize + SAFEARRAY_HIDDEN_SIZE);

  if (!ptr)
  {
      *ppsaOut = NULL;
      return E_OUTOFMEMORY;
  }

  *ppsaOut = (SAFEARRAY*)(ptr + SAFEARRAY_HIDDEN_SIZE);
  return S_OK;
}