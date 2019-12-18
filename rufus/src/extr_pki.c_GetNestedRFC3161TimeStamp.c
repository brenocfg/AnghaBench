#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long uint64_t ;
struct TYPE_13__ {size_t cAttr; TYPE_2__* rgAttr; } ;
struct TYPE_16__ {TYPE_3__ UnauthAttrs; } ;
struct TYPE_14__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
struct TYPE_15__ {TYPE_4__ Content; } ;
struct TYPE_12__ {TYPE_1__* rgValue; int /*<<< orphan*/  pszObjId; } ;
struct TYPE_11__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_5__* PCRYPT_CONTENT_INFO ;
typedef  TYPE_6__* PCMSG_SIGNER_INFO ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  int /*<<< orphan*/ * HCRYPTMSG ;
typedef  size_t DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CMSG_DETACHED_FLAG ; 
 int /*<<< orphan*/  CMSG_SIGNED ; 
 int /*<<< orphan*/  CMSG_SIGNER_INFO_PARAM ; 
 int /*<<< orphan*/  CRYPT_DECODE_ALLOC_FLAG ; 
 scalar_t__ CryptDecodeObjectEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  CryptMsgClose (int /*<<< orphan*/ *) ; 
 scalar_t__ CryptMsgGetParam (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/ * CryptMsgOpenToDecode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CryptMsgUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ENCODING ; 
 scalar_t__ FALSE ; 
 unsigned long long GetRFC3161TimeStamp (TYPE_6__*) ; 
 int /*<<< orphan*/  LocalFree (TYPE_5__*) ; 
 int /*<<< orphan*/  PKCS_7_ASN_ENCODING ; 
 int /*<<< orphan*/  PKCS_CONTENT_INFO ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WinPKIErrorString () ; 
 scalar_t__ calloc (size_t,int) ; 
 scalar_t__ lstrcmpA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_free (TYPE_6__*) ; 
 int /*<<< orphan*/  szOID_NESTED_SIGNATURE ; 
 int /*<<< orphan*/  uprintf (char*,...) ; 

__attribute__((used)) static uint64_t GetNestedRFC3161TimeStamp(PCMSG_SIGNER_INFO pSignerInfo)
{
	BOOL r, found = FALSE;
	DWORD n, dwSize = 0;
	PCRYPT_CONTENT_INFO pNestedSignature = NULL;
	PCMSG_SIGNER_INFO pNestedSignerInfo = NULL;
	HCRYPTMSG hMsg = NULL;
	uint64_t ts = 0ULL;

	// Loop through unauthenticated attributes for szOID_NESTED_SIGNATURE OID
	for (n = 0; ; n++) {
		if (pNestedSignature != NULL) {
			LocalFree(pNestedSignature);
			pNestedSignature = NULL;
		}
		if (hMsg != NULL) {
			CryptMsgClose(hMsg);
			hMsg = NULL;
		}
		safe_free(pNestedSignerInfo);
		if (n >= pSignerInfo->UnauthAttrs.cAttr)
			break;
		if (lstrcmpA(pSignerInfo->UnauthAttrs.rgAttr[n].pszObjId, szOID_NESTED_SIGNATURE) == 0) {
			if (found) {
				uprintf("PKI: Multiple nested signatures found. This could indicate something very nasty...");
				return 0ULL;
			}
			found = TRUE;
			r = CryptDecodeObjectEx(PKCS_7_ASN_ENCODING, PKCS_CONTENT_INFO,
				pSignerInfo->UnauthAttrs.rgAttr[n].rgValue[0].pbData,
				pSignerInfo->UnauthAttrs.rgAttr[n].rgValue[0].cbData,
				CRYPT_DECODE_ALLOC_FLAG, NULL, (PVOID)&pNestedSignature, &dwSize);
			if (!r) {
				uprintf("PKI: Could not retrieve nested signature data: %s", WinPKIErrorString());
				continue;
			}

			hMsg = CryptMsgOpenToDecode(ENCODING, CMSG_DETACHED_FLAG, CMSG_SIGNED, (HCRYPTPROV)NULL, NULL, NULL);
			if (hMsg == NULL) {
				uprintf("PKI: Could not create nested signature message: %s", WinPKIErrorString());
				continue;
			}
			r = CryptMsgUpdate(hMsg, pNestedSignature->Content.pbData, pNestedSignature->Content.cbData, TRUE);
			if (!r) {
				uprintf("PKI: Could not update message: %s", WinPKIErrorString());
				continue;
			}
			// Get nested signer
			r = CryptMsgGetParam(hMsg, CMSG_SIGNER_INFO_PARAM, 0, NULL, &dwSize);
			if (!r) {
				uprintf("PKI: Failed to get nested signer size: %s", WinPKIErrorString());
				continue;
			}
			pNestedSignerInfo = (PCMSG_SIGNER_INFO)calloc(dwSize, 1);
			if (!pNestedSignerInfo) {
				uprintf("PKI: Could not allocate memory for nested signer");
				continue;
			}
			r = CryptMsgGetParam(hMsg, CMSG_SIGNER_INFO_PARAM, 0, (PVOID)pNestedSignerInfo, &dwSize);
			if (!r) {
				uprintf("PKI: Failed to get nested signer information: %s", WinPKIErrorString());
				continue;
			}
			ts = GetRFC3161TimeStamp(pNestedSignerInfo);
		}
	}
	return ts;
}