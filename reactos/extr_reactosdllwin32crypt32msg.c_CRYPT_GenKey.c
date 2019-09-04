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
struct TYPE_5__ {int /*<<< orphan*/  pszObjId; } ;
struct TYPE_6__ {int /*<<< orphan*/  hContentEncryptKey; int /*<<< orphan*/  hCryptProv; TYPE_1__ ContentEncryptionAlgorithm; } ;
typedef  int /*<<< orphan*/  (* PFN_CMSG_GEN_CONTENT_ENCRYPT_KEY ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/ * HCRYPTOIDFUNCSET ;
typedef  int /*<<< orphan*/  HCRYPTOIDFUNCADDR ;
typedef  TYPE_2__ CMSG_CONTENT_ENCRYPT_INFO ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  ALG_ID ;

/* Variables and functions */
 int /*<<< orphan*/  CMSG_OID_GEN_CONTENT_ENCRYPT_KEY_FUNC ; 
 int /*<<< orphan*/  CRYPT_EXPORTABLE ; 
 int /*<<< orphan*/  CryptFreeOIDFunctionAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptGenKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CryptGetOIDFunctionAddress (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CryptInitOIDFunctionSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 

__attribute__((used)) static BOOL CRYPT_GenKey(CMSG_CONTENT_ENCRYPT_INFO *info, ALG_ID algID)
{
    static HCRYPTOIDFUNCSET set = NULL;
    PFN_CMSG_GEN_CONTENT_ENCRYPT_KEY genKeyFunc = NULL;
    HCRYPTOIDFUNCADDR hFunc;
    BOOL ret;

    if (!set)
        set = CryptInitOIDFunctionSet(CMSG_OID_GEN_CONTENT_ENCRYPT_KEY_FUNC, 0);
    CryptGetOIDFunctionAddress(set, X509_ASN_ENCODING,
     info->ContentEncryptionAlgorithm.pszObjId, 0, (void **)&genKeyFunc, &hFunc);
    if (genKeyFunc)
    {
        ret = genKeyFunc(info, 0, NULL);
        CryptFreeOIDFunctionAddress(hFunc, 0);
    }
    else
        ret = CryptGenKey(info->hCryptProv, algID, CRYPT_EXPORTABLE,
         &info->hContentEncryptKey);
    return ret;
}