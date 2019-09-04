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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {int /*<<< orphan*/  type; int /*<<< orphan*/  type_name; int /*<<< orphan*/  file; int /*<<< orphan*/  pSymbols; int /*<<< orphan*/  bArrayType; } ;
typedef  TYPE_1__* PVRET ;
typedef  scalar_t__ LPSTR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int) ; 
 int /*<<< orphan*/  ExtractNumber (scalar_t__) ; 
 int /*<<< orphan*/  ExtractTypeName (scalar_t__) ; 
 int /*<<< orphan*/  ExtractTypeNumber (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FindTypeDefinition (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PICE_strchr (scalar_t__,char) ; 
 int /*<<< orphan*/  PICE_strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN ExtractArray(PVRET pvr,LPSTR p)
{
    ULONG index_typenumber,type_number;
    ULONG lower_bound,upper_bound;
    LPSTR pTypeDef;

    DPRINT((1,"ExtractArray(%s)\n",p));

    // index-type index-type-number;lower;upper;element-type-number
    pvr->bArrayType = TRUE;
    p++;
    index_typenumber = ExtractTypeNumber(p);
    p = PICE_strchr(p,';');
    if(p)
    {
        p++;
        lower_bound = ExtractNumber(p);
        p = PICE_strchr(p,';');
        if(p)
        {
            p++;

            upper_bound = ExtractNumber(p);
            p = PICE_strchr(p,';');
            if(p)
            {
                p++;

                type_number = ExtractTypeNumber(p);

                DPRINT((1,"ExtractArray(): %x %x %x %x\n",index_typenumber,lower_bound,upper_bound,type_number));

                pTypeDef = FindTypeDefinition(pvr->pSymbols,type_number,pvr->file);
                if(pTypeDef)
                {
                    PICE_strcpy(pvr->type_name,ExtractTypeName(pTypeDef));
                    pvr->type = type_number;
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}