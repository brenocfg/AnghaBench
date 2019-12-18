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
 int /*<<< orphan*/  fclose_file_func ; 
 int /*<<< orphan*/  ferror_file_func ; 
 int /*<<< orphan*/  fopen64_file_func ; 
 int /*<<< orphan*/  fread_file_func ; 
 int /*<<< orphan*/  fseek64_file_func ; 
 int /*<<< orphan*/  ftell64_file_func ; 
 int /*<<< orphan*/  fwrite_file_func ; 

void fill_fopen64_filefunc (zlib_filefunc64_def*  pzlib_filefunc_def)
{
    pzlib_filefunc_def->zopen64_file = fopen64_file_func;
    pzlib_filefunc_def->zread_file = fread_file_func;
    pzlib_filefunc_def->zwrite_file = fwrite_file_func;
    pzlib_filefunc_def->ztell64_file = ftell64_file_func;
    pzlib_filefunc_def->zseek64_file = fseek64_file_func;
    pzlib_filefunc_def->zclose_file = fclose_file_func;
    pzlib_filefunc_def->zerror_file = ferror_file_func;
    pzlib_filefunc_def->opaque = NULL;
}