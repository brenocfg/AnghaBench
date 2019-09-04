#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_7__ {int len; char* deformatted; int n; } ;
struct TYPE_6__ {int len; int type; int n; void* nonprop; void* propfound; } ;
typedef  char* LPWSTR ;
typedef  TYPE_1__ FORMSTR ;
typedef  TYPE_2__ FORMAT ;
typedef  int DWORD ;
typedef  void* BOOL ;

/* Variables and functions */
 int lstrlenW (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* msi_alloc (int) ; 
 TYPE_1__* msi_alloc_zero (int) ; 
 int /*<<< orphan*/  msi_free (char*) ; 

__attribute__((used)) static FORMSTR *format_replace( FORMAT *format, BOOL propfound, BOOL nonprop,
                                int oldsize, int type, WCHAR *replace, int len )
{
    FORMSTR *ret;
    LPWSTR str, ptr;
    DWORD size = 0;
    int n;

    if (replace)
    {
        if (!len)
            size = 1;
        else
            size = len;
    }

    size -= oldsize;
    size = format->len + size + 1;

    if (size <= 1)
    {
        msi_free(format->deformatted);
        format->deformatted = NULL;
        format->len = 0;
        return NULL;
    }

    str = msi_alloc(size * sizeof(WCHAR));
    if (!str)
        return NULL;

    str[0] = '\0';
    memcpy(str, format->deformatted, format->n * sizeof(WCHAR));
    n = format->n;

    if (replace)
    {
        if (!len) str[n++] = 0;
        else
        {
            memcpy( str + n, replace, len * sizeof(WCHAR) );
            n += len;
            str[n] = 0;
        }
    }

    ptr = &format->deformatted[format->n + oldsize];
    memcpy(&str[n], ptr, (lstrlenW(ptr) + 1) * sizeof(WCHAR));

    msi_free(format->deformatted);
    format->deformatted = str;
    format->len = size - 1;

    /* don't reformat the NULL */
    if (replace && !len)
        format->n++;

    if (!replace)
        return NULL;

    ret = msi_alloc_zero(sizeof(FORMSTR));
    if (!ret)
        return NULL;

    ret->len = len;
    ret->type = type;
    ret->n = format->n;
    ret->propfound = propfound;
    ret->nonprop = nonprop;

    return ret;
}