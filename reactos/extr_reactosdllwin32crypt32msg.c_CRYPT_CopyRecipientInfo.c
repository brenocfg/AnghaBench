#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ cbData; } ;
struct TYPE_6__ {int /*<<< orphan*/  Issuer; int /*<<< orphan*/  SerialNumber; } ;
struct TYPE_5__ {TYPE_4__ Issuer; TYPE_4__ SerialNumber; } ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_1__ CERT_ISSUER_SERIAL_NUMBER ;
typedef  TYPE_2__ CERT_INFO ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_CopyBlob (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ERROR_MORE_DATA ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,void*,...) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL CRYPT_CopyRecipientInfo(void *pvData, DWORD *pcbData,
 const CERT_ISSUER_SERIAL_NUMBER *in)
{
    DWORD size = sizeof(CERT_INFO);
    BOOL ret;

    TRACE("(%p, %d, %p)\n", pvData, pvData ? *pcbData : 0, in);

    size += in->SerialNumber.cbData;
    size += in->Issuer.cbData;
    if (!pvData)
    {
        *pcbData = size;
        ret = TRUE;
    }
    else if (*pcbData < size)
    {
        *pcbData = size;
        SetLastError(ERROR_MORE_DATA);
        ret = FALSE;
    }
    else
    {
        LPBYTE nextData = (BYTE *)pvData + sizeof(CERT_INFO);
        CERT_INFO *out = pvData;

        CRYPT_CopyBlob(&out->SerialNumber, &in->SerialNumber, &nextData);
        CRYPT_CopyBlob(&out->Issuer, &in->Issuer, &nextData);
        ret = TRUE;
    }
    TRACE("returning %d\n", ret);
    return ret;
}