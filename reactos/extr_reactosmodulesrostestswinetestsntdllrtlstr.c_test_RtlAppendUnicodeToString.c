#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_4__ {scalar_t__ Length; scalar_t__ MaximumLength; char* Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
struct TYPE_5__ {scalar_t__ dest_Length; scalar_t__ dest_MaximumLength; int dest_buf_size; scalar_t__ result; scalar_t__ res_Length; scalar_t__ res_MaximumLength; scalar_t__ res_buf; int /*<<< orphan*/  res_buf_size; scalar_t__ src; int /*<<< orphan*/ * dest_buf; } ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 unsigned int NB_APP_UNI2STR ; 
 TYPE_3__* app_uni2str ; 
 scalar_t__ memcmp (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ok (int,char*,unsigned int,char*,scalar_t__) ; 
 scalar_t__ pRtlAppendUnicodeToString (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_RtlAppendUnicodeToString(void)
{
    WCHAR dest_buf[257];
    UNICODE_STRING dest_str;
    NTSTATUS result;
    unsigned int test_num;

    for (test_num = 0; test_num < NB_APP_UNI2STR; test_num++) {
	dest_str.Length        = app_uni2str[test_num].dest_Length;
	dest_str.MaximumLength = app_uni2str[test_num].dest_MaximumLength;
	if (app_uni2str[test_num].dest_buf != NULL) {
	    memcpy(dest_buf, app_uni2str[test_num].dest_buf, app_uni2str[test_num].dest_buf_size);
	    dest_buf[app_uni2str[test_num].dest_buf_size/sizeof(WCHAR)] = '\0';
	    dest_str.Buffer = dest_buf;
	} else {
	    dest_str.Buffer = NULL;
	}
	result = pRtlAppendUnicodeToString(&dest_str, (LPCWSTR) app_uni2str[test_num].src);
	ok(result == app_uni2str[test_num].result,
           "(test %d): RtlAppendUnicodeToString(dest, src) has result %x, expected %x\n",
	   test_num, result, app_uni2str[test_num].result);
	ok(dest_str.Length == app_uni2str[test_num].res_Length,
	   "(test %d): RtlAppendUnicodeToString(dest, src) dest has Length %d, expected %d\n",
	   test_num, dest_str.Length, app_uni2str[test_num].res_Length);
	ok(dest_str.MaximumLength == app_uni2str[test_num].res_MaximumLength,
	   "(test %d): RtlAppendUnicodeToString(dest, src) dest has MaximumLength %d, expected %d\n",
	   test_num, dest_str.MaximumLength, app_uni2str[test_num].res_MaximumLength);
	if (dest_str.Buffer == dest_buf) {
	    ok(memcmp(dest_buf, app_uni2str[test_num].res_buf, app_uni2str[test_num].res_buf_size) == 0,
	       "(test %d): RtlAppendUnicodeToString(dest, src) has dest \"%s\" expected \"%s\"\n",
	       test_num, (char *) dest_buf, app_uni2str[test_num].res_buf);
	} else {
	    ok(dest_str.Buffer == (WCHAR *) app_uni2str[test_num].res_buf,
	       "(test %d): RtlAppendUnicodeToString(dest, src) dest has Buffer %p expected %p\n",
	       test_num, dest_str.Buffer, app_uni2str[test_num].res_buf);
	}
    }
}