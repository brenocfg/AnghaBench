#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_15__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_31__ {TYPE_15__* pbData; } ;
struct TYPE_29__ {TYPE_15__* pbData; } ;
struct TYPE_30__ {TYPE_7__ Parameters; } ;
struct TYPE_26__ {TYPE_15__* pbData; } ;
struct TYPE_24__ {TYPE_15__* pbData; } ;
struct TYPE_23__ {TYPE_15__* pbData; } ;
struct TYPE_25__ {TYPE_2__ SerialNumber; TYPE_1__ Issuer; } ;
struct TYPE_27__ {TYPE_4__ KeyId; TYPE_3__ IssuerSerialNumber; } ;
struct TYPE_28__ {scalar_t__ dwIdChoice; TYPE_5__ u; } ;
struct TYPE_22__ {size_t cValue; struct TYPE_22__* pszObjId; struct TYPE_22__* rgValue; struct TYPE_22__* pbData; } ;
struct TYPE_20__ {size_t cAttr; TYPE_15__* rgAttr; } ;
struct TYPE_19__ {size_t cAttr; TYPE_15__* rgAttr; } ;
struct TYPE_18__ {TYPE_15__* pbData; } ;
struct TYPE_17__ {TYPE_9__ Parameters; } ;
struct TYPE_21__ {TYPE_13__ UnauthAttrs; TYPE_12__ AuthAttrs; TYPE_11__ EncryptedHash; TYPE_10__ HashEncryptionAlgorithm; TYPE_8__ HashAlgorithm; TYPE_6__ SignerId; } ;
typedef  size_t DWORD ;
typedef  TYPE_14__ CMSG_CMS_SIGNER_INFO ;

/* Variables and functions */
 scalar_t__ CERT_ID_ISSUER_SERIAL_NUMBER ; 
 int /*<<< orphan*/  CryptMemFree (TYPE_15__*) ; 

__attribute__((used)) static void CSignerInfo_Free(CMSG_CMS_SIGNER_INFO *info)
{
    DWORD i, j;

    if (info->SignerId.dwIdChoice == CERT_ID_ISSUER_SERIAL_NUMBER)
    {
        CryptMemFree(info->SignerId.u.IssuerSerialNumber.Issuer.pbData);
        CryptMemFree(info->SignerId.u.IssuerSerialNumber.SerialNumber.pbData);
    }
    else
        CryptMemFree(info->SignerId.u.KeyId.pbData);
    CryptMemFree(info->HashAlgorithm.Parameters.pbData);
    CryptMemFree(info->HashEncryptionAlgorithm.Parameters.pbData);
    CryptMemFree(info->EncryptedHash.pbData);
    for (i = 0; i < info->AuthAttrs.cAttr; i++)
    {
        for (j = 0; j < info->AuthAttrs.rgAttr[i].cValue; j++)
            CryptMemFree(info->AuthAttrs.rgAttr[i].rgValue[j].pbData);
        CryptMemFree(info->AuthAttrs.rgAttr[i].rgValue);
        CryptMemFree(info->AuthAttrs.rgAttr[i].pszObjId);
    }
    CryptMemFree(info->AuthAttrs.rgAttr);
    for (i = 0; i < info->UnauthAttrs.cAttr; i++)
    {
        for (j = 0; j < info->UnauthAttrs.rgAttr[i].cValue; j++)
            CryptMemFree(info->UnauthAttrs.rgAttr[i].rgValue[j].pbData);
        CryptMemFree(info->UnauthAttrs.rgAttr[i].rgValue);
        CryptMemFree(info->UnauthAttrs.rgAttr[i].pszObjId);
    }
    CryptMemFree(info->UnauthAttrs.rgAttr);
}