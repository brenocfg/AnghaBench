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
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/ * HCRYPTMSG ;
typedef  TYPE_1__ CMSG_STREAM_INFO ;
typedef  TYPE_2__ CMSG_HASHED_ENCODE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  CMSG_DATA ; 
 int /*<<< orphan*/  CMSG_DETACHED_FLAG ; 
 int /*<<< orphan*/  CryptMsgClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CryptMsgOpenToEncode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,char*,TYPE_1__*) ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  PKCS_7_ASN_ENCODING ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_data_msg_open(void)
{
    HCRYPTMSG msg;
    CMSG_HASHED_ENCODE_INFO hashInfo = { 0 };
    CMSG_STREAM_INFO streamInfo = { 0 };
    char oid[] = "1.2.3";

    /* The data message type takes no additional info */
    SetLastError(0xdeadbeef);
    msg = CryptMsgOpenToEncode(PKCS_7_ASN_ENCODING, 0, CMSG_DATA, &hashInfo,
     NULL, NULL);
    ok(!msg && GetLastError() == E_INVALIDARG,
     "Expected E_INVALIDARG, got %x\n", GetLastError());
    msg = CryptMsgOpenToEncode(PKCS_7_ASN_ENCODING, 0, CMSG_DATA, NULL, NULL,
     NULL);
    ok(msg != NULL, "CryptMsgOpenToEncode failed: %x\n", GetLastError());
    CryptMsgClose(msg);

    /* An empty stream info is allowed. */
    msg = CryptMsgOpenToEncode(PKCS_7_ASN_ENCODING, 0, CMSG_DATA, NULL, NULL,
     &streamInfo);
    ok(msg != NULL, "CryptMsgOpenToEncode failed: %x\n", GetLastError());
    CryptMsgClose(msg);

    /* Passing a bogus inner OID succeeds for a non-streamed message.. */
    msg = CryptMsgOpenToEncode(PKCS_7_ASN_ENCODING, 0, CMSG_DATA, NULL, oid,
     NULL);
    ok(msg != NULL, "CryptMsgOpenToEncode failed: %x\n", GetLastError());
    CryptMsgClose(msg);
    /* and still succeeds when CMSG_DETACHED_FLAG is passed.. */
    msg = CryptMsgOpenToEncode(PKCS_7_ASN_ENCODING, CMSG_DETACHED_FLAG,
     CMSG_DATA, NULL, oid, NULL);
    ok(msg != NULL, "CryptMsgOpenToEncode failed: %x\n", GetLastError());
    CryptMsgClose(msg);
    /* and when a stream info is given, even though you're not supposed to be
     * able to use anything but szOID_RSA_data when streaming is being used.
     */
    msg = CryptMsgOpenToEncode(PKCS_7_ASN_ENCODING, CMSG_DETACHED_FLAG,
     CMSG_DATA, NULL, oid, &streamInfo);
    ok(msg != NULL, "CryptMsgOpenToEncode failed: %x\n", GetLastError());
    CryptMsgClose(msg);
}