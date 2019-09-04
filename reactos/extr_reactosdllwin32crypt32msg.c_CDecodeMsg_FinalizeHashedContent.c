#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  hash; } ;
struct TYPE_14__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
struct TYPE_13__ {int open_flags; } ;
struct TYPE_18__ {TYPE_3__ u; int /*<<< orphan*/  properties; TYPE_2__ detached_data; TYPE_1__ base; int /*<<< orphan*/  crypt_prov; } ;
struct TYPE_17__ {int /*<<< orphan*/  pszObjId; } ;
struct TYPE_16__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CRYPT_DER_BLOB ;
typedef  TYPE_4__ CRYPT_DATA_BLOB ;
typedef  TYPE_5__ CRYPT_ALGORITHM_IDENTIFIER ;
typedef  TYPE_6__ CDecodeMsg ;
typedef  scalar_t__ BOOL ;
typedef  int /*<<< orphan*/  ALG_ID ;

/* Variables and functions */
 int /*<<< orphan*/  CMSG_CONTENT_PARAM ; 
 int CMSG_CRYPT_RELEASE_CONTEXT_FLAG ; 
 int CMSG_DETACHED_FLAG ; 
 int /*<<< orphan*/  CMSG_HASH_ALGORITHM_PARAM ; 
 int /*<<< orphan*/  CertOIDToAlgId (int /*<<< orphan*/ ) ; 
 scalar_t__ ContextPropertyList_FindProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ CryptCreateHash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CryptHashData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* CryptMemAlloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptMemFree (TYPE_5__*) ; 
 scalar_t__ CryptMsgGetParam (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  I_CryptGetDefaultCryptProv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL CDecodeMsg_FinalizeHashedContent(CDecodeMsg *msg,
 CRYPT_DER_BLOB *blob)
{
    CRYPT_ALGORITHM_IDENTIFIER *hashAlgoID = NULL;
    DWORD size = 0;
    ALG_ID algID = 0;
    BOOL ret;

    CryptMsgGetParam(msg, CMSG_HASH_ALGORITHM_PARAM, 0, NULL, &size);
    hashAlgoID = CryptMemAlloc(size);
    ret = CryptMsgGetParam(msg, CMSG_HASH_ALGORITHM_PARAM, 0, hashAlgoID,
     &size);
    if (ret)
        algID = CertOIDToAlgId(hashAlgoID->pszObjId);

    if (!msg->crypt_prov)
    {
        msg->crypt_prov = I_CryptGetDefaultCryptProv(algID);
        if (msg->crypt_prov)
            msg->base.open_flags &= ~CMSG_CRYPT_RELEASE_CONTEXT_FLAG;
    }

    ret = CryptCreateHash(msg->crypt_prov, algID, 0, 0, &msg->u.hash);
    if (ret)
    {
        CRYPT_DATA_BLOB content;

        if (msg->base.open_flags & CMSG_DETACHED_FLAG)
        {
            /* Unlike for non-detached messages, the data were never stored as
             * the content param, but were saved in msg->detached_data instead.
             */
            content.pbData = msg->detached_data.pbData;
            content.cbData = msg->detached_data.cbData;
        }
        else
            ret = ContextPropertyList_FindProperty(msg->properties,
             CMSG_CONTENT_PARAM, &content);
        if (ret)
            ret = CryptHashData(msg->u.hash, content.pbData, content.cbData, 0);
    }
    CryptMemFree(hashAlgoID);
    return ret;
}