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
struct TYPE_3__ {scalar_t__ removeType; int /*<<< orphan*/ * objects; } ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ DropStmt ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  EXTENSION_NAME ; 
 scalar_t__ OBJECT_EXTENSION ; 
 int /*<<< orphan*/  extension_exists () ; 
 void* linitial (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 char* strVal (void*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
drop_statement_drops_extension(DropStmt *stmt)
{
	if (!extension_exists())
		return false;

	if (stmt->removeType == OBJECT_EXTENSION)
	{
		if (list_length(stmt->objects) == 1)
		{
			char *ext_name;
#if PG96
			List *names = linitial(stmt->objects);

			Assert(list_length(names) == 1);
			ext_name = strVal(linitial(names));
#else
			void *name = linitial(stmt->objects);

			ext_name = strVal(name);
#endif
			if (strcmp(ext_name, EXTENSION_NAME) == 0)
				return true;
		}
	}
	return false;
}