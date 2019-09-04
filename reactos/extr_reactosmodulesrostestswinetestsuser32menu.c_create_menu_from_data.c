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
struct menu_data {int /*<<< orphan*/  str; int /*<<< orphan*/  id; int /*<<< orphan*/  type; } ;
typedef  size_t INT ;
typedef  scalar_t__ HMENU ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AppendMenuA (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateMenu () ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HMENU create_menu_from_data(const struct menu_data *item, INT item_count)
{
    HMENU hmenu;
    INT i;
    BOOL ret;

    hmenu = CreateMenu();
    assert(hmenu != 0);

    for (i = 0; i < item_count; i++)
    {
        SetLastError(0xdeadbeef);
        ret = AppendMenuA(hmenu, item[i].type, item[i].id, item[i].str);
        ok(ret, "%d: AppendMenu(%04x, %04x, %p) error %u\n",
           i, item[i].type, item[i].id, item[i].str, GetLastError());
    }
    return hmenu;
}