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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ USHORT ;
struct TYPE_5__ {int Length; int MaximumLength; int /*<<< orphan*/ * Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
struct TYPE_6__ {scalar_t__ result; scalar_t__ pos; int /*<<< orphan*/ * search_chars; int /*<<< orphan*/ * main_str; int /*<<< orphan*/  flags; } ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 unsigned int NB_FIND_CH_IN_USTR ; 
 TYPE_4__* find_ch_in_ustr ; 
 int /*<<< orphan*/  ok (int,char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ pRtlFindCharInUnicodeString (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,scalar_t__*) ; 
 int strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_RtlFindCharInUnicodeString(void)
{
    WCHAR main_str_buf[257];
    WCHAR search_chars_buf[257];
    UNICODE_STRING main_str;
    UNICODE_STRING search_chars;
    USHORT pos;
    NTSTATUS result;
    unsigned int idx;
    unsigned int test_num;

    if (!pRtlFindCharInUnicodeString)
    {
        win_skip("RtlFindCharInUnicodeString is not available\n");
        return;
    }

    for (test_num = 0; test_num < NB_FIND_CH_IN_USTR; test_num++) {
	if (find_ch_in_ustr[test_num].main_str != NULL) {
	    main_str.Length        = strlen(find_ch_in_ustr[test_num].main_str) * sizeof(WCHAR);
	    main_str.MaximumLength = main_str.Length + sizeof(WCHAR);
	    for (idx = 0; idx < main_str.Length / sizeof(WCHAR); idx++) {
		main_str_buf[idx] = find_ch_in_ustr[test_num].main_str[idx];
	    }
	    main_str.Buffer = main_str_buf;
	} else {
	    main_str.Length        = 0;
	    main_str.MaximumLength = 0;
	    main_str.Buffer        = NULL;
	}
	if (find_ch_in_ustr[test_num].search_chars != NULL) {
	    search_chars.Length        = strlen(find_ch_in_ustr[test_num].search_chars) * sizeof(WCHAR);
	    search_chars.MaximumLength = search_chars.Length + sizeof(WCHAR);
	    for (idx = 0; idx < search_chars.Length / sizeof(WCHAR); idx++) {
		search_chars_buf[idx] = find_ch_in_ustr[test_num].search_chars[idx];
	    }
	    search_chars.Buffer = search_chars_buf;
	} else {
	    search_chars.Length        = 0;
	    search_chars.MaximumLength = 0;
	    search_chars.Buffer        = NULL;
	}
	pos = 12345;
        result = pRtlFindCharInUnicodeString(find_ch_in_ustr[test_num].flags, &main_str, &search_chars, &pos);
        ok(result == find_ch_in_ustr[test_num].result,
           "(test %d): RtlFindCharInUnicodeString(%d, %s, %s, [out]) has result %x, expected %x\n",
           test_num, find_ch_in_ustr[test_num].flags,
           find_ch_in_ustr[test_num].main_str, find_ch_in_ustr[test_num].search_chars,
           result, find_ch_in_ustr[test_num].result);
        ok(pos == find_ch_in_ustr[test_num].pos,
           "(test %d): RtlFindCharInUnicodeString(%d, %s, %s, [out]) assigns %d to pos, expected %d\n",
           test_num, find_ch_in_ustr[test_num].flags,
           find_ch_in_ustr[test_num].main_str, find_ch_in_ustr[test_num].search_chars,
           pos, find_ch_in_ustr[test_num].pos);
    }
}