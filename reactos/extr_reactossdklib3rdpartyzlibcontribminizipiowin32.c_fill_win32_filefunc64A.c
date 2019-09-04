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
struct TYPE_3__ {int /*<<< orphan*/ * opaque; int /*<<< orphan*/  zerror_file; int /*<<< orphan*/  zclose_file; int /*<<< orphan*/  zseek64_file; int /*<<< orphan*/  ztell64_file; int /*<<< orphan*/  zwrite_file; int /*<<< orphan*/  zread_file; int /*<<< orphan*/  zopen64_file; } ;
typedef  TYPE_1__ zlib_filefunc64_def ;

/* Variables and functions */
 int /*<<< orphan*/  win32_close_file_func ; 
 int /*<<< orphan*/  win32_error_file_func ; 
 int /*<<< orphan*/  win32_open64_file_funcA ; 
 int /*<<< orphan*/  win32_read_file_func ; 
 int /*<<< orphan*/  win32_seek64_file_func ; 
 int /*<<< orphan*/  win32_tell64_file_func ; 
 int /*<<< orphan*/  win32_write_file_func ; 

void fill_win32_filefunc64A(zlib_filefunc64_def* pzlib_filefunc_def)
{
    pzlib_filefunc_def->zopen64_file = win32_open64_file_funcA;
    pzlib_filefunc_def->zread_file = win32_read_file_func;
    pzlib_filefunc_def->zwrite_file = win32_write_file_func;
    pzlib_filefunc_def->ztell64_file = win32_tell64_file_func;
    pzlib_filefunc_def->zseek64_file = win32_seek64_file_func;
    pzlib_filefunc_def->zclose_file = win32_close_file_func;
    pzlib_filefunc_def->zerror_file = win32_error_file_func;
    pzlib_filefunc_def->opaque = NULL;
}