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
struct TYPE_4__ {char* name; int /*<<< orphan*/  attrs; } ;
typedef  TYPE_1__ type_t ;
typedef  int /*<<< orphan*/  UUID ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_UUID ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * get_attrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* uuid_string (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  write_guid (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  write_uuid_decl (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void write_coclass(FILE *header, type_t *cocl)
{
  const UUID *uuid = get_attrp(cocl->attrs, ATTR_UUID);

  fprintf(header, "/*****************************************************************************\n");
  fprintf(header, " * %s coclass\n", cocl->name);
  fprintf(header, " */\n\n");
  if (uuid)
      write_guid(header, "CLSID", cocl->name, uuid);
  fprintf(header, "\n#ifdef __cplusplus\n");
  if (uuid)
  {
      fprintf(header, "class DECLSPEC_UUID(\"%s\") %s;\n", uuid_string(uuid), cocl->name);
      write_uuid_decl(header, cocl, uuid);
  }
  else
  {
      fprintf(header, "class %s;\n", cocl->name);
  }
  fprintf(header, "#endif\n");
  fprintf(header, "\n");
}