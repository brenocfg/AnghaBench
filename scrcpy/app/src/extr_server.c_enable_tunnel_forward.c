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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  process_t ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKET_NAME ; 
 int /*<<< orphan*/  adb_forward (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int process_check_success (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool
enable_tunnel_forward(const char *serial, uint16_t local_port) {
    process_t process = adb_forward(serial, local_port, SOCKET_NAME);
    return process_check_success(process, "adb forward");
}