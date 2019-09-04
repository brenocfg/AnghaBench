#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_8__ {scalar_t__ BaseAddress; } ;
struct TYPE_7__ {int ulOffsetToStabs; int ulSizeOfStabs; int ulOffsetToStabsStrings; } ;
struct TYPE_6__ {int n_strx; int n_type; int n_value; } ;
typedef  int /*<<< orphan*/  STAB_ENTRY ;
typedef  int* PULONG ;
typedef  TYPE_1__* PSTAB_ENTRY ;
typedef  TYPE_2__ PICE_SYMBOLFILE_HEADER ;
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int CurrentEBP ; 
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int ExtractTypeNumber (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int FindFunctionInModuleByName (char*,TYPE_3__*) ; 
 TYPE_2__* FindModuleSymbols (int) ; 
#define  N_GSYM 132 
#define  N_LSYM 131 
#define  N_PSYM 130 
#define  N_SO 129 
#define  N_UNDF 128 
 int /*<<< orphan*/  PICE_strcat (char*,char*) ; 
 char* PICE_strchr (char*,char) ; 
 int /*<<< orphan*/  PICE_strcmpi (char*,char*) ; 
 int /*<<< orphan*/  PICE_strcpy (char*,char*) ; 
 int PICE_strlen (char*) ; 
 int /*<<< orphan*/  PICE_strncpy (char*,char*,int) ; 
 int StrLenUpToWhiteChar (char*,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__* pCurrentMod ; 

BOOLEAN FindGlobalStabSymbol(LPSTR pExpression,PULONG pValue,PULONG pulTypeNumber,PULONG pulFileNumber)
{
  ULONG i;
  PSTAB_ENTRY pStab;
  LPSTR pStr,pName;
  int nStabLen;
  int nOffset=0,nNextOffset=0,nLen,strLen;
  PICE_SYMBOLFILE_HEADER* pSymbols;
  ULONG ulTypeNumber;
  static char SymbolName[1024];
  static char szCurrentPath[256];
  ULONG ulCurrentFileNumber=0;
  LPSTR pTypeDefIncluded;
  ULONG addr;

  // must have a current module
  if(pCurrentMod)
    {
      // in case we query for the kernel we need to use the fake kernel module
      addr = (ULONG)pCurrentMod->BaseAddress;

      // find the symbols for the module
      pSymbols = FindModuleSymbols(addr);
      if(pSymbols)
	{
	  // prepare table access
	  pStab = (PSTAB_ENTRY )((ULONG)pSymbols + pSymbols->ulOffsetToStabs);
	  nStabLen = pSymbols->ulSizeOfStabs;
	  pStr = (LPSTR)((ULONG)pSymbols + pSymbols->ulOffsetToStabsStrings);
	  // starting at file 0
	  *pulFileNumber = 0;

	  // go through stabs
	  for(i=0;i<(nStabLen/sizeof(STAB_ENTRY));i++)
	    {
	      pName = &pStr[pStab->n_strx + nOffset];

	      switch(pStab->n_type)
		{
		  // an N_UNDF symbol marks a change of string table offset
		case N_UNDF:
		  nOffset += nNextOffset;
		  nNextOffset = pStab->n_value;
		  break;
		  // a source file symbol
		case N_SO:
		  if((strLen = PICE_strlen(pName)))
		    {
		      if(pName[strLen-1]!='/')
			{
			  ulCurrentFileNumber++;
			  if(PICE_strlen(szCurrentPath))
			    {
			      PICE_strcat(szCurrentPath,pName);
			      DPRINT((0,"changing source file %s\n",szCurrentPath));
			    }
			  else
			    {
			      DPRINT((0,"changing source file %s\n",pName));
			    }
			}
		      else
			PICE_strcpy(szCurrentPath,pName);
		    }
		  else
		    {
		      szCurrentPath[0]=0;
		    }
		  break;
		case N_GSYM:
		case N_LSYM:
		case N_PSYM:
		  // symbol-name:type-identifier type-number =
		  nLen = StrLenUpToWhiteChar(pName,":");
		  PICE_strncpy(SymbolName,pName,nLen);
		  SymbolName[nLen] = 0;
		  if(PICE_strcmpi(SymbolName,pExpression)==0)
		    {
		      DPRINT((0,"global symbol %s\n",pName));
		      // extract type-number from stab
		      ulTypeNumber = ExtractTypeNumber(pName);
		      DPRINT((0,"type number = %x, from %s\n",ulTypeNumber, pName));
		      *pulTypeNumber = ulTypeNumber;
		      // look for symbols address in external symbols
		      if( pStab->n_type == N_LSYM || pStab->n_type == N_PSYM )
			*pValue = CurrentEBP + pStab->n_value;
		      else *pValue = FindFunctionInModuleByName(SymbolName,pCurrentMod);

		      DPRINT((0,"value = %x\n",*pValue));
		      *pulFileNumber = ulCurrentFileNumber;
		      DPRINT((0,"file = %x\n",ulCurrentFileNumber));
		      if((pTypeDefIncluded = PICE_strchr(pName,'=')) )
			{
			  DPRINT((0,"symbol includes type definition (%s)\n",pTypeDefIncluded));
			}
		      return TRUE;
		    }
		  break;
		}
	      pStab++;
	    }
	}
    }
  return FALSE;
}