#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nullParams ;
struct TYPE_10__ {int /*<<< orphan*/  properties; } ;
struct TYPE_8__ {int cbData; int /*<<< orphan*/ * pbData; } ;
struct TYPE_9__ {TYPE_1__ Parameters; scalar_t__ pszObjId; } ;
typedef  scalar_t__ LPSTR ;
typedef  int DWORD ;
typedef  TYPE_2__ CRYPT_ALGORITHM_IDENTIFIER ;
typedef  TYPE_3__ CDecodeMsg ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
#define  ASN_NULL 128 
 int /*<<< orphan*/  ContextPropertyList_SetProperty (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* CryptMemAlloc (int) ; 
 int /*<<< orphan*/  CryptMemFree (TYPE_2__*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcpy (scalar_t__,scalar_t__) ; 
 int strlen (scalar_t__) ; 

__attribute__((used)) static void CDecodeMsg_SaveAlgorithmID(CDecodeMsg *msg, DWORD param,
 const CRYPT_ALGORITHM_IDENTIFIER *id)
{
    static const BYTE nullParams[] = { ASN_NULL, 0 };
    CRYPT_ALGORITHM_IDENTIFIER *copy;
    DWORD len = sizeof(CRYPT_ALGORITHM_IDENTIFIER);

    /* Linearize algorithm id */
    len += strlen(id->pszObjId) + 1;
    len += id->Parameters.cbData;
    copy = CryptMemAlloc(len);
    if (copy)
    {
        copy->pszObjId =
         (LPSTR)((BYTE *)copy + sizeof(CRYPT_ALGORITHM_IDENTIFIER));
        strcpy(copy->pszObjId, id->pszObjId);
        copy->Parameters.pbData = (BYTE *)copy->pszObjId + strlen(id->pszObjId)
         + 1;
        /* Trick:  omit NULL parameters */
        if (id->Parameters.cbData == sizeof(nullParams) &&
         !memcmp(id->Parameters.pbData, nullParams, sizeof(nullParams)))
        {
            copy->Parameters.cbData = 0;
            len -= sizeof(nullParams);
        }
        else
            copy->Parameters.cbData = id->Parameters.cbData;
        if (copy->Parameters.cbData)
            memcpy(copy->Parameters.pbData, id->Parameters.pbData,
             id->Parameters.cbData);
        ContextPropertyList_SetProperty(msg->properties, param, (BYTE *)copy,
         len);
        CryptMemFree(copy);
    }
}