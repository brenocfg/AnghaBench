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
 int /*<<< orphan*/  print_proxy (char*) ; 

__attribute__((used)) static void write_stubdescproto(void)
{
  print_proxy( "static const MIDL_STUB_DESC Object_StubDesc;\n");
  print_proxy( "\n");
}