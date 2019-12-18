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
typedef  scalar_t__ LONG ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 scalar_t__ RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok (int,char*,char*,scalar_t__) ; 

__attribute__((used)) static void ok_registry(BOOL expectsuccess)
{
    LONG ret;

    /* Functional tests for success of install and clean up */
    ret = RegDeleteKeyA(HKEY_CURRENT_USER, "Software\\Wine\\setupapitest");
    ok((expectsuccess && ret == ERROR_SUCCESS) ||
       (!expectsuccess && ret == ERROR_FILE_NOT_FOUND),
       "Expected registry key Software\\Wine\\setupapitest to %s, RegDeleteKey returned %d\n",
       expectsuccess ? "exist" : "not exist",
       ret);
}