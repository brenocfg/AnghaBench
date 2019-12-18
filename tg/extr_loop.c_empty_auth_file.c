#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ test_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  TG_SERVER_1 ; 
 int /*<<< orphan*/  TG_SERVER_2 ; 
 int /*<<< orphan*/  TG_SERVER_3 ; 
 int /*<<< orphan*/  TG_SERVER_4 ; 
 int /*<<< orphan*/  TG_SERVER_5 ; 
 int /*<<< orphan*/  TG_SERVER_DEFAULT ; 
 int /*<<< orphan*/  TG_SERVER_TEST_1 ; 
 int /*<<< orphan*/  TG_SERVER_TEST_2 ; 
 int /*<<< orphan*/  TG_SERVER_TEST_3 ; 
 int /*<<< orphan*/  TG_SERVER_TEST_DEFAULT ; 
 TYPE_1__* TLS ; 
 int /*<<< orphan*/  bl_do_dc_option (TYPE_1__*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bl_do_set_working_dc (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void empty_auth_file (void) {
  if (TLS->test_mode) {
    bl_do_dc_option (TLS, 0, 1, "", 0, TG_SERVER_TEST_1, strlen (TG_SERVER_TEST_1), 443);
    bl_do_dc_option (TLS, 0, 2, "", 0, TG_SERVER_TEST_2, strlen (TG_SERVER_TEST_2), 443);
    bl_do_dc_option (TLS, 0, 3, "", 0, TG_SERVER_TEST_3, strlen (TG_SERVER_TEST_3), 443);
    bl_do_set_working_dc (TLS, TG_SERVER_TEST_DEFAULT);
  } else {
    bl_do_dc_option (TLS, 0, 1, "", 0, TG_SERVER_1, strlen (TG_SERVER_1), 443);
    bl_do_dc_option (TLS, 0, 2, "", 0, TG_SERVER_2, strlen (TG_SERVER_2), 443);
    bl_do_dc_option (TLS, 0, 3, "", 0, TG_SERVER_3, strlen (TG_SERVER_3), 443);
    bl_do_dc_option (TLS, 0, 4, "", 0, TG_SERVER_4, strlen (TG_SERVER_4), 443);
    bl_do_dc_option (TLS, 0, 5, "", 0, TG_SERVER_5, strlen (TG_SERVER_5), 443);
    bl_do_set_working_dc (TLS, TG_SERVER_DEFAULT);
  }
}