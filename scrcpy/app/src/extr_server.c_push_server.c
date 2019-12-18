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
typedef  int /*<<< orphan*/  process_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_SERVER_PATH ; 
 int /*<<< orphan*/  adb_push (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_server_path () ; 
 int process_check_success (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool
push_server(const char *serial) {
    process_t process = adb_push(serial, get_server_path(), DEVICE_SERVER_PATH);
    return process_check_success(process, "adb push");
}