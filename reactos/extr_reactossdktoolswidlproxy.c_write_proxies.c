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
typedef  int /*<<< orphan*/  statement_list_t ;

/* Variables and functions */
 scalar_t__ do_everything ; 
 int /*<<< orphan*/  do_proxies ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_proxy (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  need_proxy_file (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  proxy ; 
 int /*<<< orphan*/  write_proxy_routines (int /*<<< orphan*/  const*) ; 

void write_proxies(const statement_list_t *stmts)
{
  if (!do_proxies) return;
  if (do_everything && !need_proxy_file(stmts)) return;

  init_proxy(stmts);
  if(!proxy) return;

  write_proxy_routines( stmts );
  fclose(proxy);
}