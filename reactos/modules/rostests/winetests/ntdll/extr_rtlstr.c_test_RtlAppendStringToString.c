#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ dest_Length; scalar_t__ dest_MaximumLength; size_t dest_buf_size; scalar_t__ src_Length; scalar_t__ src_MaximumLength; size_t src_buf_size; scalar_t__ result; scalar_t__ res_Length; scalar_t__ res_MaximumLength; scalar_t__ res_buf; int /*<<< orphan*/  res_buf_size; int /*<<< orphan*/ * src_buf; int /*<<< orphan*/ * dest_buf; } ;
struct TYPE_5__ {scalar_t__ Length; scalar_t__ MaximumLength; char* Buffer; } ;
typedef  TYPE_1__ STRING ;
typedef  scalar_t__ NTSTATUS ;
typedef  char CHAR ;

/* Variables and functions */
 unsigned int NB_APP_STR2STR ; 
 TYPE_4__* app_str2str ; 
 scalar_t__ memcmp (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ok (int,char*,unsigned int,char*,scalar_t__) ; 
 scalar_t__ pRtlAppendStringToString (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static void test_RtlAppendStringToString(void)
{
    CHAR dest_buf[257];
    CHAR src_buf[257];
    STRING dest_str;
    STRING src_str;
    NTSTATUS result;
    unsigned int test_num;

    for (test_num = 0; test_num < NB_APP_STR2STR; test_num++) {
	dest_str.Length        = app_str2str[test_num].dest_Length;
	dest_str.MaximumLength = app_str2str[test_num].dest_MaximumLength;
	if (app_str2str[test_num].dest_buf != NULL) {
	    memcpy(dest_buf, app_str2str[test_num].dest_buf, app_str2str[test_num].dest_buf_size);
	    dest_buf[app_str2str[test_num].dest_buf_size] = '\0';
	    dest_str.Buffer = dest_buf;
	} else {
	    dest_str.Buffer = NULL;
	}
	src_str.Length         = app_str2str[test_num].src_Length;
	src_str.MaximumLength  = app_str2str[test_num].src_MaximumLength;
	if (app_str2str[test_num].src_buf != NULL) {
	    memcpy(src_buf, app_str2str[test_num].src_buf, app_str2str[test_num].src_buf_size);
	    src_buf[app_str2str[test_num].src_buf_size] = '\0';
	    src_str.Buffer = src_buf;
	} else {
	    src_str.Buffer = NULL;
	}
	result = pRtlAppendStringToString(&dest_str, &src_str);
	ok(result == app_str2str[test_num].result,
           "(test %d): RtlAppendStringToString(dest, src) has result %x, expected %x\n",
	   test_num, result, app_str2str[test_num].result);
	ok(dest_str.Length == app_str2str[test_num].res_Length,
	   "(test %d): RtlAppendStringToString(dest, src) dest has Length %d, expected %d\n",
	   test_num, dest_str.Length, app_str2str[test_num].res_Length);
	ok(dest_str.MaximumLength == app_str2str[test_num].res_MaximumLength,
	   "(test %d): RtlAppendStringToString(dest, src) dest has MaximumLength %d, expected %d\n",
	   test_num, dest_str.MaximumLength, app_str2str[test_num].res_MaximumLength);
	if (dest_str.Buffer == dest_buf) {
	    ok(memcmp(dest_buf, app_str2str[test_num].res_buf, app_str2str[test_num].res_buf_size) == 0,
	       "(test %d): RtlAppendStringToString(dest, src) has dest \"%s\" expected \"%s\"\n",
	       test_num, dest_buf, app_str2str[test_num].res_buf);
	} else {
	    ok(dest_str.Buffer == app_str2str[test_num].res_buf,
	       "(test %d): RtlAppendStringToString(dest, src) dest has Buffer %p expected %p\n",
	       test_num, dest_str.Buffer, app_str2str[test_num].res_buf);
	}
    }
}