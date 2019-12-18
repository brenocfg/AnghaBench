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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {int cbData; scalar_t__ pbData; } ;
struct TYPE_6__ {scalar_t__ dwValueType; TYPE_1__ Value; } ;
typedef  TYPE_2__ CERT_NAME_VALUE ;

/* Variables and functions */
 scalar_t__ CERT_RDN_ENCODED_BLOB ; 
 scalar_t__ CERT_RDN_UTF8_STRING ; 
 int /*<<< orphan*/  memcmp (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void compareNameValues(const CERT_NAME_VALUE *expected,
 const CERT_NAME_VALUE *got)
{
    if (expected->dwValueType == CERT_RDN_UTF8_STRING &&
        got->dwValueType == CERT_RDN_ENCODED_BLOB)
    {
        win_skip("Can't handle CERT_RDN_UTF8_STRING\n");
        return;
    }

    ok(got->dwValueType == expected->dwValueType,
     "Expected string type %d, got %d\n", expected->dwValueType,
     got->dwValueType);
    ok(got->Value.cbData == expected->Value.cbData ||
     got->Value.cbData == expected->Value.cbData - sizeof(WCHAR) /* Win8 */,
     "String type %d: unexpected data size, got %d, expected %d\n",
     expected->dwValueType, got->Value.cbData, expected->Value.cbData);
    if (got->Value.cbData && got->Value.pbData)
        ok(!memcmp(got->Value.pbData, expected->Value.pbData,
         min(got->Value.cbData, expected->Value.cbData)),
         "String type %d: unexpected value\n", expected->dwValueType);
}