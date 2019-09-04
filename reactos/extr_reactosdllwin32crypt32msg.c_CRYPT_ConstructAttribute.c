#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rgValue; int /*<<< orphan*/  cValue; scalar_t__ pszObjId; } ;
typedef  TYPE_1__ CRYPT_ATTRIBUTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_ConstructBlobArray (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CryptMemAlloc (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  strcpy (scalar_t__,scalar_t__) ; 
 scalar_t__ strlen (scalar_t__) ; 

__attribute__((used)) static BOOL CRYPT_ConstructAttribute(CRYPT_ATTRIBUTE *out,
 const CRYPT_ATTRIBUTE *in)
{
    BOOL ret;

    out->pszObjId = CryptMemAlloc(strlen(in->pszObjId) + 1);
    if (out->pszObjId)
    {
        strcpy(out->pszObjId, in->pszObjId);
        ret = CRYPT_ConstructBlobArray(&out->cValue, &out->rgValue,
         in->cValue, in->rgValue);
    }
    else
        ret = FALSE;
    return ret;
}