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
struct module {int dummy; } ;
struct CoffFileSet {int nfiles; int nfiles_alloc; struct CoffFile* files; } ;
struct CoffFile {int startaddr; int linetab_offset; scalar_t__ neps_alloc; scalar_t__ neps; int /*<<< orphan*/ * entries; scalar_t__ linecnt; int /*<<< orphan*/  compiland; scalar_t__ endaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 struct CoffFile* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct CoffFile* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct CoffFile*,int) ; 
 int /*<<< orphan*/  source_new (struct module*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  symt_new_compiland (struct module*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int coff_add_file(struct CoffFileSet* coff_files, struct module* module,
                         const char* filename)
{
    struct CoffFile* file;

    if (coff_files->nfiles + 1 >= coff_files->nfiles_alloc)
    {
        if (coff_files->files)
        {
            coff_files->nfiles_alloc *= 2;
            coff_files->files = HeapReAlloc(GetProcessHeap(), 0, coff_files->files,
                                            coff_files->nfiles_alloc * sizeof(struct CoffFile));
        }
        else
        {
            coff_files->nfiles_alloc = 16;
            coff_files->files = HeapAlloc(GetProcessHeap(), 0,
                                          coff_files->nfiles_alloc * sizeof(struct CoffFile));
        }
    }
    file = coff_files->files + coff_files->nfiles;
    file->startaddr = 0xffffffff;
    file->endaddr   = 0;
    file->compiland = symt_new_compiland(module, 0,
                                         source_new(module, NULL, filename));
    file->linetab_offset = -1;
    file->linecnt = 0;
    file->entries = NULL;
    file->neps = file->neps_alloc = 0;

    return coff_files->nfiles++;
}