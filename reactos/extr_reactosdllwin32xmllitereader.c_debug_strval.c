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
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ strval ;

/* Variables and functions */
 char const* debugstr_wn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reader_get_strptr (int /*<<< orphan*/  const*,TYPE_1__ const*) ; 

__attribute__((used)) static inline const char* debug_strval(const xmlreader *reader, const strval *v)
{
    return debugstr_wn(reader_get_strptr(reader, v), v->len);
}