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
typedef  int /*<<< orphan*/  type ;
struct TYPE_3__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
typedef  int /*<<< orphan*/ * HCRYPTMSG ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_1__ CRYPT_DATA_BLOB ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CERT_QUERY_CONTENT_PKCS7_SIGNED ; 
 scalar_t__ CMSG_SIGNED ; 
 int /*<<< orphan*/  CMSG_TYPE_PARAM ; 
 int /*<<< orphan*/  CryptMsgClose (int /*<<< orphan*/ *) ; 
 scalar_t__ CryptMsgGetParam (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/ * CryptMsgOpenToDecode (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CryptMsgUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 scalar_t__ FALSE ; 
 scalar_t__ PKCS_7_ASN_ENCODING ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ X509_ASN_ENCODING ; 

__attribute__((used)) static BOOL CRYPT_QuerySignedMessage(const CRYPT_DATA_BLOB *blob,
 DWORD *pdwMsgAndCertEncodingType, DWORD *pdwContentType, HCRYPTMSG *phMsg)
{
    DWORD encodingType = X509_ASN_ENCODING | PKCS_7_ASN_ENCODING;
    BOOL ret = FALSE;
    HCRYPTMSG msg;

    if ((msg = CryptMsgOpenToDecode(encodingType, 0, 0, 0, NULL, NULL)))
    {
        ret = CryptMsgUpdate(msg, blob->pbData, blob->cbData, TRUE);
        if (ret)
        {
            DWORD type, len = sizeof(type);

            ret = CryptMsgGetParam(msg, CMSG_TYPE_PARAM, 0, &type, &len);
            if (ret)
            {
                if (type != CMSG_SIGNED)
                {
                    SetLastError(ERROR_INVALID_DATA);
                    ret = FALSE;
                }
            }
        }
        if (!ret)
        {
            CryptMsgClose(msg);
            msg = CryptMsgOpenToDecode(encodingType, 0, CMSG_SIGNED, 0, NULL,
             NULL);
            if (msg)
            {
                ret = CryptMsgUpdate(msg, blob->pbData, blob->cbData, TRUE);
                if (!ret)
                {
                    CryptMsgClose(msg);
                    msg = NULL;
                }
            }
        }
    }
    if (ret)
    {
        if (pdwMsgAndCertEncodingType)
            *pdwMsgAndCertEncodingType = encodingType;
        if (pdwContentType)
            *pdwContentType = CERT_QUERY_CONTENT_PKCS7_SIGNED;
        if (phMsg)
            *phMsg = msg;
    }
    return ret;
}