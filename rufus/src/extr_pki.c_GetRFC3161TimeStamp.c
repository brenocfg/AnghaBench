#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  unsigned long long uint64_t ;
struct TYPE_11__ {size_t cAttr; TYPE_2__* rgAttr; } ;
struct TYPE_14__ {TYPE_3__ UnauthAttrs; } ;
struct TYPE_12__ {size_t cbData; int /*<<< orphan*/ * pbData; } ;
struct TYPE_13__ {TYPE_4__ Content; } ;
struct TYPE_10__ {TYPE_1__* rgValue; int /*<<< orphan*/  pszObjId; } ;
struct TYPE_9__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_5__* PCRYPT_CONTENT_INFO ;
typedef  TYPE_6__* PCMSG_SIGNER_INFO ;
typedef  size_t DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_DECODE_ALLOC_FLAG ; 
 scalar_t__ CryptDecodeObjectEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  DumpBufferHex (char*,size_t) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LocalFree (TYPE_5__*) ; 
 int /*<<< orphan*/  PKCS_7_ASN_ENCODING ; 
 int /*<<< orphan*/  PKCS_CONTENT_INFO ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WinPKIErrorString () ; 
 void* get_data_from_asn1 (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ lstrcmpA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long long strtoull (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  szOID_RFC3161_counterSign ; 
 int /*<<< orphan*/ * szOID_TIMESTAMP_TOKEN ; 
 int /*<<< orphan*/  uprintf (char*,...) ; 

__attribute__((used)) static uint64_t GetRFC3161TimeStamp(PCMSG_SIGNER_INFO pSignerInfo)
{
	BOOL r, found = FALSE;
	DWORD n, dwSize = 0;
	PCRYPT_CONTENT_INFO pCounterSignerInfo = NULL;
	uint64_t ts = 0ULL;
	uint8_t *timestamp_token;
	size_t timestamp_token_size;
	char* timestamp_str;
	size_t timestamp_str_size;

	// Loop through unauthenticated attributes for szOID_RFC3161_counterSign OID
	for (n = 0; n < pSignerInfo->UnauthAttrs.cAttr; n++) {
		if (lstrcmpA(pSignerInfo->UnauthAttrs.rgAttr[n].pszObjId, szOID_RFC3161_counterSign) == 0) {
			// Depending on how Microsoft implemented their timestamp checks, and the fact that we are dealing
			// with UnauthAttrs, there's a possibility that an attacker may add a "fake" RFC 3161 countersigner
			// to try to trick us into using their timestamp data. Detect that.
			if (found) {
				uprintf("PKI: Multiple RFC 3161 countersigners found. This could indicate something very nasty...");
				return 0ULL;
			}
			found = TRUE;

			// Read the countersigner message data
			r = CryptDecodeObjectEx(PKCS_7_ASN_ENCODING, PKCS_CONTENT_INFO,
				pSignerInfo->UnauthAttrs.rgAttr[n].rgValue[0].pbData,
				pSignerInfo->UnauthAttrs.rgAttr[n].rgValue[0].cbData,
				CRYPT_DECODE_ALLOC_FLAG, NULL, (PVOID)&pCounterSignerInfo, &dwSize);
			if (!r) {
				uprintf("PKI: Could not retrieve RFC 3161 countersigner data: %s", WinPKIErrorString());
				continue;
			}

			// Get the RFC 3161 timestamp message
			timestamp_token = get_data_from_asn1(pCounterSignerInfo->Content.pbData,
				pCounterSignerInfo->Content.cbData, szOID_TIMESTAMP_TOKEN,
				// 0x04 = "Octet String" ASN.1 tag
				0x04, &timestamp_token_size);
			if (timestamp_token) {
				timestamp_str = get_data_from_asn1(timestamp_token, timestamp_token_size, NULL,
					// 0x18 = "Generalized Time" ASN.1 tag
					0x18, &timestamp_str_size);
				if (timestamp_str) {
					// As per RFC 3161 The syntax is: YYYYMMDDhhmmss[.s...]Z
					if ((timestamp_str_size < 14) || (timestamp_str[timestamp_str_size - 1] != 'Z')) {
						// Sanity checks
						uprintf("PKI: Not an RFC 3161 timestamp");
						DumpBufferHex(timestamp_str, timestamp_str_size);
					} else {
						ts = strtoull(timestamp_str, NULL, 10);
					}
				}
			}
			LocalFree(pCounterSignerInfo);
		}
	}
	return ts;
}