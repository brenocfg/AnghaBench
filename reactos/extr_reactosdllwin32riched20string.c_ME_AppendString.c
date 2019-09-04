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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  nLen; } ;
typedef  TYPE_1__ ME_String ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ME_InsertString (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

BOOL ME_AppendString(ME_String *s, const WCHAR *append, int len)
{
    return ME_InsertString( s, s->nLen, append, len );
}