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
struct TYPE_6__ {int /*<<< orphan*/  hash; } ;
struct TYPE_8__ {int /*<<< orphan*/  properties; TYPE_1__ u; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {int cbData; int /*<<< orphan*/ * pbData; } ;
typedef  int DWORD ;
typedef  TYPE_2__ CRYPT_DATA_BLOB ;
typedef  TYPE_3__ CDecodeMsg ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  CMSG_COMPUTED_HASH_PARAM 130 
#define  CMSG_HASH_ALGORITHM_PARAM 129 
#define  CMSG_TYPE_PARAM 128 
 int /*<<< orphan*/  CRYPT_CopyParam (void*,int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CRYPT_E_INVALID_MSG_TYPE ; 
 int /*<<< orphan*/  CRYPT_FixUpAlgorithmID (void*) ; 
 int /*<<< orphan*/  ContextPropertyList_FindProperty (int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  CryptGetHashParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HP_HASHVAL ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL CDecodeHashMsg_GetParam(CDecodeMsg *msg, DWORD dwParamType,
 DWORD dwIndex, void *pvData, DWORD *pcbData)
{
    BOOL ret = FALSE;

    switch (dwParamType)
    {
    case CMSG_TYPE_PARAM:
        ret = CRYPT_CopyParam(pvData, pcbData, &msg->type, sizeof(msg->type));
        break;
    case CMSG_HASH_ALGORITHM_PARAM:
    {
        CRYPT_DATA_BLOB blob;

        ret = ContextPropertyList_FindProperty(msg->properties, dwParamType,
         &blob);
        if (ret)
        {
            ret = CRYPT_CopyParam(pvData, pcbData, blob.pbData, blob.cbData);
            if (ret && pvData)
                CRYPT_FixUpAlgorithmID(pvData);
        }
        else
            SetLastError(CRYPT_E_INVALID_MSG_TYPE);
        break;
    }
    case CMSG_COMPUTED_HASH_PARAM:
        ret = CryptGetHashParam(msg->u.hash, HP_HASHVAL, pvData, pcbData, 0);
        break;
    default:
    {
        CRYPT_DATA_BLOB blob;

        ret = ContextPropertyList_FindProperty(msg->properties, dwParamType,
         &blob);
        if (ret)
            ret = CRYPT_CopyParam(pvData, pcbData, blob.pbData, blob.cbData);
        else
            SetLastError(CRYPT_E_INVALID_MSG_TYPE);
    }
    }
    return ret;
}