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
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/ * HCRYPTMSG ;
typedef  TYPE_1__ CMSG_STREAM_INFO ;

/* Variables and functions */
 int CMSG_DATA ; 
 int CMSG_ENCRYPTED ; 
 int CMSG_ENVELOPED ; 
 int CMSG_HASHED ; 
 int CMSG_SIGNED ; 
 int CMSG_SIGNED_AND_ENVELOPED ; 
 int /*<<< orphan*/  CryptMsgClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CryptMsgOpenToDecode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  PKCS_7_ASN_ENCODING ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_msg_open_to_decode(void)
{
    HCRYPTMSG msg;
    CMSG_STREAM_INFO streamInfo = { 0 };

    SetLastError(0xdeadbeef);
    msg = CryptMsgOpenToDecode(0, 0, 0, 0, NULL, NULL);
    ok(!msg && GetLastError() == E_INVALIDARG,
     "Expected E_INVALIDARG, got %x\n", GetLastError());

    /* Bad encodings */
    SetLastError(0xdeadbeef);
    msg = CryptMsgOpenToDecode(X509_ASN_ENCODING, 0, 0, 0, NULL, NULL);
    ok(!msg && GetLastError() == E_INVALIDARG,
     "Expected E_INVALIDARG, got %x\n", GetLastError());
    SetLastError(0xdeadbeef);
    msg = CryptMsgOpenToDecode(X509_ASN_ENCODING, 0, CMSG_DATA, 0, NULL, NULL);
    ok(!msg && GetLastError() == E_INVALIDARG,
     "Expected E_INVALIDARG, got %x\n", GetLastError());

    /* The message type can be explicit... */
    msg = CryptMsgOpenToDecode(PKCS_7_ASN_ENCODING, 0, CMSG_DATA, 0, NULL,
     NULL);
    ok(msg != NULL, "CryptMsgOpenToDecode failed: %x\n", GetLastError());
    CryptMsgClose(msg);
    msg = CryptMsgOpenToDecode(PKCS_7_ASN_ENCODING, 0, CMSG_ENVELOPED, 0, NULL,
     NULL);
    ok(msg != NULL, "CryptMsgOpenToDecode failed: %x\n", GetLastError());
    CryptMsgClose(msg);
    msg = CryptMsgOpenToDecode(PKCS_7_ASN_ENCODING, 0, CMSG_HASHED, 0, NULL,
     NULL);
    ok(msg != NULL, "CryptMsgOpenToDecode failed: %x\n", GetLastError());
    CryptMsgClose(msg);
    msg = CryptMsgOpenToDecode(PKCS_7_ASN_ENCODING, 0, CMSG_SIGNED, 0, NULL,
     NULL);
    ok(msg != NULL, "CryptMsgOpenToDecode failed: %x\n", GetLastError());
    CryptMsgClose(msg);
    msg = CryptMsgOpenToDecode(PKCS_7_ASN_ENCODING, 0,
     CMSG_SIGNED_AND_ENVELOPED, 0, NULL, NULL);
    ok(msg != NULL, "CryptMsgOpenToDecode failed: %x\n", GetLastError());
    CryptMsgClose(msg);
    /* or implicit.. */
    msg = CryptMsgOpenToDecode(PKCS_7_ASN_ENCODING, 0, 0, 0, NULL, NULL);
    ok(msg != NULL, "CryptMsgOpenToDecode failed: %x\n", GetLastError());
    CryptMsgClose(msg);
    /* or even invalid. */
    msg = CryptMsgOpenToDecode(PKCS_7_ASN_ENCODING, 0, CMSG_ENCRYPTED, 0, NULL,
     NULL);
    ok(msg != NULL, "CryptMsgOpenToDecode failed: %x\n", GetLastError());
    CryptMsgClose(msg);
    msg = CryptMsgOpenToDecode(PKCS_7_ASN_ENCODING, 0, 1000, 0, NULL, NULL);
    ok(msg != NULL, "CryptMsgOpenToDecode failed: %x\n", GetLastError());
    CryptMsgClose(msg);

    /* And even though the stream info parameter "must be set to NULL" for
     * CMSG_HASHED, it's still accepted.
     */
    msg = CryptMsgOpenToDecode(PKCS_7_ASN_ENCODING, 0, CMSG_HASHED, 0, NULL,
     &streamInfo);
    ok(msg != NULL, "CryptMsgOpenToDecode failed: %x\n", GetLastError());
    CryptMsgClose(msg);
}