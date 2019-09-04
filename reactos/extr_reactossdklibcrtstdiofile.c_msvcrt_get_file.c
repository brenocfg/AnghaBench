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
struct TYPE_4__ {int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ file_crit ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int MSVCRT_FD_BLOCK_SIZE ; 
 TYPE_1__** MSVCRT_fstream ; 
 int MSVCRT_max_streams ; 
 int _IOB_ENTRIES ; 
 int /*<<< orphan*/ * _errno () ; 
 int /*<<< orphan*/ * _iob ; 
 TYPE_1__* calloc (int,int) ; 

__attribute__((used)) static inline FILE* msvcrt_get_file(int i)
{
    file_crit *ret;

    if(i >= MSVCRT_max_streams)
        return NULL;

    if(i < _IOB_ENTRIES)
        return &_iob[i];

    ret = MSVCRT_fstream[i/MSVCRT_FD_BLOCK_SIZE];
    if(!ret) {
        MSVCRT_fstream[i/MSVCRT_FD_BLOCK_SIZE] = calloc(MSVCRT_FD_BLOCK_SIZE, sizeof(file_crit));
        if(!MSVCRT_fstream[i/MSVCRT_FD_BLOCK_SIZE]) {
            ERR("out of memory\n");
            *_errno() = ENOMEM;
            return NULL;
        }

        ret = MSVCRT_fstream[i/MSVCRT_FD_BLOCK_SIZE] + (i%MSVCRT_FD_BLOCK_SIZE);
    } else
        ret += i%MSVCRT_FD_BLOCK_SIZE;

    return &ret->file;
}