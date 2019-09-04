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
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ type_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  type_alias_get_aliasee (TYPE_1__*) ; 
 int /*<<< orphan*/  write_type_def_or_decl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_typedef(FILE *header, type_t *type)
{
  fprintf(header, "typedef ");
  write_type_def_or_decl(header, type_alias_get_aliasee(type), FALSE, type->name);
  fprintf(header, ";\n");
}