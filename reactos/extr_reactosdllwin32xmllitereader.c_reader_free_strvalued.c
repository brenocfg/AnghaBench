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
typedef  int /*<<< orphan*/  xmlreader ;
struct TYPE_4__ {scalar_t__ str; } ;
typedef  TYPE_1__ strval ;

/* Variables and functions */
 int /*<<< orphan*/  reader_free (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__ strval_empty ; 

__attribute__((used)) static void reader_free_strvalued(xmlreader *reader, strval *v)
{
    if (v->str != strval_empty.str)
    {
        reader_free(reader, v->str);
        *v = strval_empty;
    }
}