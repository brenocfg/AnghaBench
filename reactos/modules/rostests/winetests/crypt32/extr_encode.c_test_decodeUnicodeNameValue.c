#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
struct TYPE_9__ {scalar_t__ valueType; int /*<<< orphan*/  str; TYPE_1__ encoded; } ;
struct TYPE_7__ {int cbData; scalar_t__ pbData; } ;
struct TYPE_8__ {scalar_t__ dwValueType; TYPE_2__ Value; } ;
typedef  TYPE_3__* PCERT_NAME_VALUE ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_4__*) ; 
 int /*<<< orphan*/  CRYPT_DECODE_ALLOC_FLAG ; 
 scalar_t__ CRYPT_E_NOT_CHAR_STRING ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_UNICODE_NAME_VALUE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,size_t,...) ; 
 scalar_t__ pCryptDecodeObjectEx (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  strncmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* unicodeResults ; 

__attribute__((used)) static void test_decodeUnicodeNameValue(DWORD dwEncoding)
{
    DWORD i;

    for (i = 0; i < ARRAY_SIZE(unicodeResults); i++)
    {
        BYTE *buf = NULL;
        BOOL ret;
        DWORD size = 0;

        ret = pCryptDecodeObjectEx(dwEncoding, X509_UNICODE_NAME_VALUE,
         unicodeResults[i].encoded.pbData, unicodeResults[i].encoded.cbData,
         CRYPT_DECODE_ALLOC_FLAG, NULL, &buf, &size);
        ok(ret || broken(GetLastError() == CRYPT_E_NOT_CHAR_STRING /* Win9x */),
         "CryptDecodeObjectEx failed: %08x\n", GetLastError());
        if (ret && buf)
        {
            PCERT_NAME_VALUE value = (PCERT_NAME_VALUE)buf;

            ok(value->dwValueType == unicodeResults[i].valueType,
             "Expected value type %d, got %d\n", unicodeResults[i].valueType,
             value->dwValueType);
            ok(!strncmpW((LPWSTR)value->Value.pbData, unicodeResults[i].str,
             value->Value.cbData / sizeof(WCHAR)),
             "Unexpected decoded value for index %d (value type %d)\n", i,
             unicodeResults[i].valueType);
            LocalFree(buf);
        }
    }
}