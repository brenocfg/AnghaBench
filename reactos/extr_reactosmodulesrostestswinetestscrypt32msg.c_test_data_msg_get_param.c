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
struct TYPE_3__ {int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  HCRYPTMSG ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_1__ CMSG_STREAM_INFO ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CMSG_BARE_CONTENT_PARAM ; 
 int /*<<< orphan*/  CMSG_COMPUTED_HASH_PARAM ; 
 int /*<<< orphan*/  CMSG_CONTENT_PARAM ; 
 int /*<<< orphan*/  CMSG_DATA ; 
 int /*<<< orphan*/  CMSG_ENCODED_SIGNER ; 
 int /*<<< orphan*/  CMSG_TYPE_PARAM ; 
 scalar_t__ CRYPT_E_INVALID_MSG_TYPE ; 
 int /*<<< orphan*/  CryptMsgClose (int /*<<< orphan*/ ) ; 
 int CryptMsgGetParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  CryptMsgOpenToEncode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  PKCS_7_ASN_ENCODING ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  nop_stream_output ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_data_msg_get_param(void)
{
    HCRYPTMSG msg;
    DWORD size;
    BOOL ret;
    CMSG_STREAM_INFO streamInfo = { 0, nop_stream_output, NULL };

    msg = CryptMsgOpenToEncode(PKCS_7_ASN_ENCODING, 0, CMSG_DATA, NULL, NULL,
     NULL);

    /* Content and bare content are always gettable when not streaming */
    size = 0;
    ret = CryptMsgGetParam(msg, CMSG_CONTENT_PARAM, 0, NULL, &size);
    ok(ret, "CryptMsgGetParam failed: %08x\n", GetLastError());
    size = 0;
    ret = CryptMsgGetParam(msg, CMSG_BARE_CONTENT_PARAM, 0, NULL, &size);
    ok(ret, "CryptMsgGetParam failed: %08x\n", GetLastError());
    /* But for this type of message, the signer and hash aren't applicable,
     * and the type isn't available.
     */
    size = 0;
    SetLastError(0xdeadbeef);
    ret = CryptMsgGetParam(msg, CMSG_ENCODED_SIGNER, 0, NULL, &size);
    ok(!ret && GetLastError() == CRYPT_E_INVALID_MSG_TYPE,
     "Expected CRYPT_E_INVALID_MSG_TYPE, got %x\n", GetLastError());
    SetLastError(0xdeadbeef);
    ret = CryptMsgGetParam(msg, CMSG_COMPUTED_HASH_PARAM, 0, NULL, &size);
    ok(!ret && GetLastError() == CRYPT_E_INVALID_MSG_TYPE,
     "Expected CRYPT_E_INVALID_MSG_TYPE, got %x\n", GetLastError());
    ret = CryptMsgGetParam(msg, CMSG_TYPE_PARAM, 0, NULL, &size);
    ok(!ret && GetLastError() == CRYPT_E_INVALID_MSG_TYPE,
     "Expected CRYPT_E_INVALID_MSG_TYPE, got %x\n", GetLastError());
    CryptMsgClose(msg);

    /* Can't get content or bare content when streaming */
    msg = CryptMsgOpenToEncode(PKCS_7_ASN_ENCODING, 0, CMSG_DATA, NULL,
     NULL, &streamInfo);
    SetLastError(0xdeadbeef);
    ret = CryptMsgGetParam(msg, CMSG_BARE_CONTENT_PARAM, 0, NULL, &size);
    ok((!ret && GetLastError() == E_INVALIDARG) || broken(ret /* Win9x */),
     "Expected E_INVALIDARG, got %x\n", GetLastError());
    SetLastError(0xdeadbeef);
    ret = CryptMsgGetParam(msg, CMSG_CONTENT_PARAM, 0, NULL, &size);
    ok((!ret && GetLastError() == E_INVALIDARG) || broken(ret /* Win9x */),
     "Expected E_INVALIDARG, got %x\n", GetLastError());
    CryptMsgClose(msg);
}