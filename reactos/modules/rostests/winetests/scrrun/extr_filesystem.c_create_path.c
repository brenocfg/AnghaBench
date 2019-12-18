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
typedef  char WCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int lstrlenW (char const*) ; 
 int /*<<< orphan*/  memmove (char*,char const*,int) ; 

__attribute__((used)) static inline void create_path(const WCHAR *folder, const WCHAR *name, WCHAR *ret)
{
    DWORD len = lstrlenW(folder);
    memmove(ret, folder, len*sizeof(WCHAR));
    ret[len] = '\\';
    memmove(ret+len+1, name, (lstrlenW(name)+1)*sizeof(WCHAR));
}