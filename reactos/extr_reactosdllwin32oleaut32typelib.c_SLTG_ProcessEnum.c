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
struct TYPE_3__ {int vars_off; int /*<<< orphan*/  cVars; } ;
typedef  TYPE_1__ SLTG_TypeInfoTail ;
typedef  int /*<<< orphan*/  SLTG_TypeInfoHeader ;
typedef  int /*<<< orphan*/  ITypeInfoImpl ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  SLTG_DoVars (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void SLTG_ProcessEnum(char *pBlk, ITypeInfoImpl *pTI,
			     const char *pNameTable, SLTG_TypeInfoHeader *pTIHeader,
			     const SLTG_TypeInfoTail *pTITail, const BYTE *hlp_strings)
{
  SLTG_DoVars(pBlk, pBlk + pTITail->vars_off, pTI, pTITail->cVars, pNameTable, NULL, hlp_strings);
}