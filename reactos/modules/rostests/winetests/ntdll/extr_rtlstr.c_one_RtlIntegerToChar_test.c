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
struct TYPE_3__ {char* result; char* Buffer; int /*<<< orphan*/  MaximumLength; int /*<<< orphan*/  base; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ int2str_t ;
typedef  char* NTSTATUS ;

/* Variables and functions */
 int STRI_BUFFER_LENGTH ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 char* pRtlIntegerToChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void one_RtlIntegerToChar_test(int test_num, const int2str_t *int2str)
{
    NTSTATUS result;
    char dest_str[STRI_BUFFER_LENGTH + 1];

    memset(dest_str, '-', STRI_BUFFER_LENGTH);
    dest_str[STRI_BUFFER_LENGTH] = '\0';
    result = pRtlIntegerToChar(int2str->value, int2str->base, int2str->MaximumLength, dest_str);
    ok(result == int2str->result,
       "(test %d): RtlIntegerToChar(%u, %d, %d, [out]) has result %x, expected: %x\n",
       test_num, int2str->value, int2str->base, int2str->MaximumLength, result, int2str->result);
    ok(memcmp(dest_str, int2str->Buffer, STRI_BUFFER_LENGTH) == 0,
       "(test %d): RtlIntegerToChar(%u, %d, %d, [out]) assigns string \"%s\", expected: \"%s\"\n",
       test_num, int2str->value, int2str->base, int2str->MaximumLength, dest_str, int2str->Buffer);
}