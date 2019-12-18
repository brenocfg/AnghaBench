#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int ERROR_FILE_NOT_FOUND ; 
 int ERROR_INVALID_CMM ; 
 int _doserrno ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int p_set_doserrno (int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test__set_doserrno(void)
{
    int ret;

    if (!p_set_doserrno)
    {
        win_skip("_set_doserrno is not available\n");
        return;
    }

    _doserrno = ERROR_INVALID_CMM;
    ret = p_set_doserrno(ERROR_FILE_NOT_FOUND);
    ok(ret == 0, "Expected _set_doserrno to return 0, got %d\n", ret);
    ok(_doserrno == ERROR_FILE_NOT_FOUND,
       "Expected _doserrno to be ERROR_FILE_NOT_FOUND, got %d\n", _doserrno);

    _doserrno = ERROR_INVALID_CMM;
    ret = p_set_doserrno(-1);
    ok(ret == 0, "Expected _set_doserrno to return 0, got %d\n", ret);
    ok(_doserrno == -1,
       "Expected _doserrno to be -1, got %d\n", _doserrno);

    _doserrno = ERROR_INVALID_CMM;
    ret = p_set_doserrno(0xdeadbeef);
    ok(ret == 0, "Expected _set_doserrno to return 0, got %d\n", ret);
    ok(_doserrno == 0xdeadbeef,
       "Expected _doserrno to be 0xdeadbeef, got %d\n", _doserrno);
}