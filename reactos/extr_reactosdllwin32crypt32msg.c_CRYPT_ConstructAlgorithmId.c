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
struct TYPE_4__ {int /*<<< orphan*/  Parameters; scalar_t__ pszObjId; } ;
typedef  TYPE_1__ CRYPT_ALGORITHM_IDENTIFIER ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_ConstructBlob (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CryptMemAlloc (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  strcpy (scalar_t__,scalar_t__) ; 
 scalar_t__ strlen (scalar_t__) ; 

__attribute__((used)) static BOOL CRYPT_ConstructAlgorithmId(CRYPT_ALGORITHM_IDENTIFIER *out,
 const CRYPT_ALGORITHM_IDENTIFIER *in)
{
    out->pszObjId = CryptMemAlloc(strlen(in->pszObjId) + 1);
    if (out->pszObjId)
    {
        strcpy(out->pszObjId, in->pszObjId);
        return CRYPT_ConstructBlob(&out->Parameters, &in->Parameters);
    }
    else
        return FALSE;
}