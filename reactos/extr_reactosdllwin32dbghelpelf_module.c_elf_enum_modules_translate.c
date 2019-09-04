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
struct elf_enum_user {int /*<<< orphan*/  user; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/  const*,unsigned long,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL elf_enum_modules_translate(const WCHAR* name, unsigned long load_addr,
                                       unsigned long dyn_addr, BOOL is_system, void* user)
{
    struct elf_enum_user*       eeu = user;
    return eeu->cb(name, load_addr, eeu->user);
}