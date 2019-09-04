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
typedef  int /*<<< orphan*/  hashInfo ;
struct TYPE_6__ {int /*<<< orphan*/  pszObjId; } ;
struct TYPE_8__ {int cbSize; TYPE_1__ HashAlgorithm; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/ * HCRYPTMSG ;
typedef  TYPE_2__ CMSG_STREAM_INFO ;
typedef  TYPE_3__ CMSG_HASHED_ENCODE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  CMSG_DETACHED_FLAG ; 
 int /*<<< orphan*/  CMSG_HASHED ; 
 scalar_t__ CRYPT_E_UNKNOWN_ALGO ; 
 int /*<<< orphan*/  CryptMsgClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CryptMsgOpenToEncode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  PKCS_7_ASN_ENCODING ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  nop_stream_output ; 
 int /*<<< orphan*/  oid_rsa_md5 ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_hash_msg_open(void)
{
    HCRYPTMSG msg;
    CMSG_HASHED_ENCODE_INFO hashInfo = { 0 };
    CMSG_STREAM_INFO streamInfo = { 0, nop_stream_output, NULL };

    SetLastError(0xdeadbeef);
    msg = CryptMsgOpenToEncode(PKCS_7_ASN_ENCODING, 0, CMSG_HASHED, &hashInfo,
     NULL, NULL);
    ok(!msg && GetLastError() == E_INVALIDARG,
     "Expected E_INVALIDARG, got %x\n", GetLastError());
    hashInfo.cbSize = sizeof(hashInfo);
    SetLastError(0xdeadbeef);
    msg = CryptMsgOpenToEncode(PKCS_7_ASN_ENCODING, 0, CMSG_HASHED, &hashInfo,
     NULL, NULL);
    ok(!msg && GetLastError() == CRYPT_E_UNKNOWN_ALGO,
     "Expected CRYPT_E_UNKNOWN_ALGO, got %x\n", GetLastError());
    hashInfo.HashAlgorithm.pszObjId = oid_rsa_md5;
    msg = CryptMsgOpenToEncode(PKCS_7_ASN_ENCODING, 0, CMSG_HASHED, &hashInfo,
     NULL, NULL);
    ok(msg != NULL, "CryptMsgOpenToEncode failed: %x\n", GetLastError());
    CryptMsgClose(msg);
    msg = CryptMsgOpenToEncode(PKCS_7_ASN_ENCODING, CMSG_DETACHED_FLAG,
     CMSG_HASHED, &hashInfo, NULL, NULL);
    ok(msg != NULL, "CryptMsgOpenToEncode failed: %x\n", GetLastError());
    CryptMsgClose(msg);
    msg = CryptMsgOpenToEncode(PKCS_7_ASN_ENCODING, CMSG_DETACHED_FLAG,
     CMSG_HASHED, &hashInfo, NULL, &streamInfo);
    ok(msg != NULL, "CryptMsgOpenToEncode failed: %x\n", GetLastError());
    CryptMsgClose(msg);
}