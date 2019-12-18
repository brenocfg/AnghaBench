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
struct tgl_state {int /*<<< orphan*/  error; int /*<<< orphan*/  error_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  logprintf (char*,...) ; 

void on_failed_login (struct tgl_state *TLS) {
  logprintf ("login failed\n");
  logprintf ("login error #%d: %s\n", TLS->error_code, TLS->error);
  logprintf ("you can relogin by deleting auth file or running telegram-cli with '-q' flag\n");
  exit (2);
}