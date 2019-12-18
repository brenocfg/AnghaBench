#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_6__ {int ulOffsetToStabs; int ulSizeOfStabs; int ulOffsetToStabsStrings; } ;
struct TYPE_5__ {int n_strx; int n_type; int n_value; } ;
typedef  int /*<<< orphan*/  STAB_ENTRY ;
typedef  TYPE_1__* PSTAB_ENTRY ;
typedef  TYPE_2__ PICE_SYMBOLFILE_HEADER ;
typedef  char* LPSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int ExtractTypeNumber (char*) ; 
 char* FindTypeDefinitionForCombinedTypes (TYPE_2__*,int,int) ; 
#define  N_LSYM 130 
#define  N_SO 129 
#define  N_UNDF 128 
 int /*<<< orphan*/  PICE_strcat (char*,char*) ; 
 char* PICE_strchr (char*,char) ; 
 int /*<<< orphan*/  PICE_strcpy (char*,char*) ; 
 int PICE_strlen (char*) ; 
 int /*<<< orphan*/  strrchr (char*,char) ; 

LPSTR FindTypeDefinition(PICE_SYMBOLFILE_HEADER* pSymbols,ULONG ulTypeNumber,ULONG ulFileNumber)
{
    ULONG i;
    PSTAB_ENTRY pStab;
    LPSTR pStr,pName,pTypeString;
    int nStabLen;
    int nOffset=0,nNextOffset=0,strLen;
	static char szAccumulatedName[2048];
	ULONG ulCurrentTypeNumber,ulCurrentFileNumber=0;
	LPSTR pTypeSymbol;
    static char szCurrentPath[256];

    ENTER_FUNC();
    DPRINT((0,"FindTypeDefinition(%u,%u)\n",ulTypeNumber,ulFileNumber));

	*szAccumulatedName = 0;

    pStab = (PSTAB_ENTRY )((ULONG)pSymbols + pSymbols->ulOffsetToStabs);
    nStabLen = pSymbols->ulSizeOfStabs;
    pStr = (LPSTR)((ULONG)pSymbols + pSymbols->ulOffsetToStabsStrings);

    for(i=0;i<(nStabLen/sizeof(STAB_ENTRY));i++)
    {
        pName = &pStr[pStab->n_strx + nOffset];

        switch(pStab->n_type)
        {
	case N_UNDF:
	  nOffset += nNextOffset;
	  nNextOffset = pStab->n_value;
	  break;
	case N_SO:
	  if((strLen = PICE_strlen(pName)))
	    {
	      if(pName[strLen-1]!='/')
		{
		  ulCurrentFileNumber++;
		  if(PICE_strlen(szCurrentPath))
		    {
		      PICE_strcat(szCurrentPath,pName);
		      DPRINT((0,"FindTypeDefinition()1: cha %s, %u\n",szCurrentPath, ulCurrentFileNumber));
		    }
		  else
		    {
		      DPRINT((0,"FindTypeDefinition(): cha %s, %u\n",pName, ulCurrentFileNumber));
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
	case N_LSYM:
				// stab has no value -> must be type definition
				//ei File number count is not reliable
	  if(pStab->n_value == 0 /*&& ulCurrentFileNumber==ulFileNumber*/)
	    {
	      DPRINT((0,"FindTypeDefinition(): pre type definition %s\n",pName));
	      // handle multi-line symbols
	      if(strrchr(pName,'\\'))
		{
		  if(PICE_strlen(szAccumulatedName))
		    {
		      PICE_strcat(szAccumulatedName,pName);
		      DPRINT((0,"FindTypeDefinition(): [1] accum. %s\n",szAccumulatedName));
		    }
		  else
		    {
		      PICE_strcpy(szAccumulatedName,pName);
		      DPRINT((0,"FindTypeDefinition(): [2] accum. %s\n",szAccumulatedName));
		    }
		  szAccumulatedName[PICE_strlen(szAccumulatedName)-1]=0;
		}
	      else
		{
		  DPRINT((0,"FindTypeDefinition(): [3] accum. %s, pname: %s\n",szAccumulatedName, pName));
		  if(PICE_strlen(szAccumulatedName)==0)
		    {
		      PICE_strcpy(szAccumulatedName,pName);
		    }
		  else
		    {
		      PICE_strcat(szAccumulatedName,pName);
		    }
		  pTypeString = szAccumulatedName;

		  pTypeSymbol = PICE_strchr(pTypeString,':');
		  if(pTypeSymbol && (*(pTypeSymbol+1)=='t' || *(pTypeSymbol+1)=='T'))
		    {
		      // parse it
		      ulCurrentTypeNumber = ExtractTypeNumber(pTypeString);
		      DPRINT((0,"FindTypeDefinition(): ulCurrType: %u, LSYM is type %s\n",ulCurrentTypeNumber,pName));
		      if(ulCurrentTypeNumber == ulTypeNumber)
			{
			  DPRINT((0,"FindTypeDefinition(): type definition %s\n",pTypeString));
			  return pTypeString;
			}
		    }
		  *szAccumulatedName=0;
		}
	    }
	  break;
        }
        pStab++;
    }

    return FindTypeDefinitionForCombinedTypes(pSymbols,ulTypeNumber,ulFileNumber);

}