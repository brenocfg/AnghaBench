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
struct file_op {int /*<<< orphan*/ * dst_file; int /*<<< orphan*/ * dst_path; int /*<<< orphan*/ * src_file; int /*<<< orphan*/ * src_path; int /*<<< orphan*/ * src_root; } ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {scalar_t__ Flags; scalar_t__ Win32Error; int /*<<< orphan*/ * Target; int /*<<< orphan*/ * Source; } ;
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  TYPE_1__ FILEPATHS_W ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int HeapSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  concat_W (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strlenW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL build_filepathsW( const struct file_op *op, FILEPATHS_W *paths )
{
    unsigned int src_len = 1, dst_len = 1;
    WCHAR *source = (PWSTR)paths->Source, *target = (PWSTR)paths->Target;

    if (op->src_root) src_len += strlenW(op->src_root) + 1;
    if (op->src_path) src_len += strlenW(op->src_path) + 1;
    if (op->src_file) src_len += strlenW(op->src_file) + 1;
    if (op->dst_path) dst_len += strlenW(op->dst_path) + 1;
    if (op->dst_file) dst_len += strlenW(op->dst_file) + 1;
    src_len *= sizeof(WCHAR);
    dst_len *= sizeof(WCHAR);

    if (!source || HeapSize( GetProcessHeap(), 0, source ) < src_len )
    {
        HeapFree( GetProcessHeap(), 0, source );
        paths->Source = source = HeapAlloc( GetProcessHeap(), 0, src_len );
    }
    if (!target || HeapSize( GetProcessHeap(), 0, target ) < dst_len )
    {
        HeapFree( GetProcessHeap(), 0, target );
        paths->Target = target = HeapAlloc( GetProcessHeap(), 0, dst_len );
    }
    if (!source || !target) return FALSE;
    concat_W( source, op->src_root, op->src_path, op->src_file );
    concat_W( target, NULL, op->dst_path, op->dst_file );
    paths->Win32Error = 0;
    paths->Flags      = 0;
    return TRUE;
}