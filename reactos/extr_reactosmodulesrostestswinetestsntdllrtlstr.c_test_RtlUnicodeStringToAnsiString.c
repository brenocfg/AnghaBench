#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_7__ {int /*<<< orphan*/ * Buffer; int /*<<< orphan*/  MaximumLength; int /*<<< orphan*/  Length; } ;
typedef  TYPE_1__ UNICODE_STRING ;
struct TYPE_9__ {scalar_t__ ansi_Length; scalar_t__ ansi_MaximumLength; size_t ansi_buf_size; int uni_buf_size; scalar_t__ result; scalar_t__ res_Length; scalar_t__ res_MaximumLength; scalar_t__ res_buf; scalar_t__ doalloc; int /*<<< orphan*/  res_buf_size; int /*<<< orphan*/ * uni_buf; int /*<<< orphan*/  uni_MaximumLength; int /*<<< orphan*/  uni_Length; int /*<<< orphan*/ * ansi_buf; } ;
struct TYPE_8__ {scalar_t__ Length; scalar_t__ MaximumLength; char* Buffer; } ;
typedef  TYPE_2__ STRING ;
typedef  scalar_t__ NTSTATUS ;
typedef  char CHAR ;

/* Variables and functions */
 unsigned int NB_USTR2ASTR ; 
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ memcmp (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ok (int,char*,unsigned int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pRtlFreeAnsiString (TYPE_2__*) ; 
 scalar_t__ pRtlUnicodeStringToAnsiString (TYPE_2__*,TYPE_1__*,scalar_t__) ; 
 TYPE_3__* ustr2astr ; 

__attribute__((used)) static void test_RtlUnicodeStringToAnsiString(void)
{
    size_t pos;
    CHAR ansi_buf[257];
    WCHAR uni_buf[257];
    STRING ansi_str;
    UNICODE_STRING uni_str;
    NTSTATUS result;
    unsigned int test_num;

    for (test_num = 0; test_num < NB_USTR2ASTR; test_num++) {
	ansi_str.Length        = ustr2astr[test_num].ansi_Length;
	ansi_str.MaximumLength = ustr2astr[test_num].ansi_MaximumLength;
	if (ustr2astr[test_num].ansi_buf != NULL) {
	    memcpy(ansi_buf, ustr2astr[test_num].ansi_buf, ustr2astr[test_num].ansi_buf_size);
	    ansi_buf[ustr2astr[test_num].ansi_buf_size] = '\0';
	    ansi_str.Buffer = ansi_buf;
	} else {
	    ansi_str.Buffer = NULL;
	}
	uni_str.Length        = ustr2astr[test_num].uni_Length;
	uni_str.MaximumLength = ustr2astr[test_num].uni_MaximumLength;
	if (ustr2astr[test_num].uni_buf != NULL) {
	    for (pos = 0; pos < ustr2astr[test_num].uni_buf_size/sizeof(WCHAR); pos++) {
		uni_buf[pos] = ustr2astr[test_num].uni_buf[pos];
	    }
	    uni_str.Buffer = uni_buf;
	} else {
	    uni_str.Buffer = NULL;
	}
	result = pRtlUnicodeStringToAnsiString(&ansi_str, &uni_str, ustr2astr[test_num].doalloc);
	ok(result == ustr2astr[test_num].result,
           "(test %d): RtlUnicodeStringToAnsiString(ansi, uni, %d) has result %x, expected %x\n",
	   test_num, ustr2astr[test_num].doalloc, result, ustr2astr[test_num].result);
	ok(ansi_str.Length == ustr2astr[test_num].res_Length,
	   "(test %d): RtlUnicodeStringToAnsiString(ansi, uni, %d) ansi has Length %d, expected %d\n",
	   test_num, ustr2astr[test_num].doalloc, ansi_str.Length, ustr2astr[test_num].res_Length);
	ok(ansi_str.MaximumLength == ustr2astr[test_num].res_MaximumLength,
	   "(test %d): RtlUnicodeStringToAnsiString(ansi, uni, %d) ansi has MaximumLength %d, expected %d\n",
	   test_num, ustr2astr[test_num].doalloc, ansi_str.MaximumLength, ustr2astr[test_num].res_MaximumLength);
	ok(memcmp(ansi_str.Buffer, ustr2astr[test_num].res_buf, ustr2astr[test_num].res_buf_size) == 0,
	   "(test %d): RtlUnicodeStringToAnsiString(ansi, uni, %d) has ansi \"%s\" expected \"%s\"\n",
	   test_num, ustr2astr[test_num].doalloc, ansi_str.Buffer, ustr2astr[test_num].res_buf);
        if(result == STATUS_SUCCESS && ustr2astr[test_num].doalloc)
            pRtlFreeAnsiString(&ansi_str);
    }
}