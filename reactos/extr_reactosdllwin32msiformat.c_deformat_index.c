#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WCHAR ;
struct TYPE_8__ {int /*<<< orphan*/  record; } ;
struct TYPE_7__ {int len; } ;
typedef  TYPE_1__ FORMSTR ;
typedef  TYPE_2__ FORMAT ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ MSI_RecordGetStringW (int /*<<< orphan*/ ,int,scalar_t__*,int*) ; 
 scalar_t__ MSI_RecordIsNull (int /*<<< orphan*/ ,int) ; 
 int atoiW (scalar_t__*) ; 
 int /*<<< orphan*/  get_formstr_data (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  lstrcpynW (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__* msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (scalar_t__*) ; 

__attribute__((used)) static WCHAR *deformat_index( FORMAT *format, FORMSTR *str, int *ret_len )
{
    WCHAR *val, *ret;
    DWORD len;
    int field;

    if (!(val = msi_alloc( (str->len + 1) * sizeof(WCHAR) ))) return NULL;
    lstrcpynW(val, get_formstr_data(format, str), str->len + 1);
    field = atoiW( val );
    msi_free( val );

    if (MSI_RecordIsNull( format->record, field ) ||
        MSI_RecordGetStringW( format->record, field, NULL, &len )) return NULL;

    len++;
    if (!(ret = msi_alloc( len * sizeof(WCHAR) ))) return NULL;
    ret[0] = 0;
    if (MSI_RecordGetStringW( format->record, field, ret, &len ))
    {
        msi_free( ret );
        return NULL;
    }
    *ret_len = len;
    return ret;
}