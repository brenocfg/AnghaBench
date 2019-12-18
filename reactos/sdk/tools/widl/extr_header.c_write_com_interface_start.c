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
struct TYPE_3__ {char* name; char* c_name; int /*<<< orphan*/  attrs; } ;
typedef  TYPE_1__ type_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_DISPINTERFACE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int is_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_com_interface_start(FILE *header, const type_t *iface)
{
  int dispinterface = is_attr(iface->attrs, ATTR_DISPINTERFACE);
  fprintf(header, "/*****************************************************************************\n");
  fprintf(header, " * %s %sinterface\n", iface->name, dispinterface ? "disp" : "");
  fprintf(header, " */\n");
  fprintf(header,"#ifndef __%s_%sINTERFACE_DEFINED__\n", iface->c_name, dispinterface ? "DISP" : "");
  fprintf(header,"#define __%s_%sINTERFACE_DEFINED__\n\n", iface->c_name, dispinterface ? "DISP" : "");
}