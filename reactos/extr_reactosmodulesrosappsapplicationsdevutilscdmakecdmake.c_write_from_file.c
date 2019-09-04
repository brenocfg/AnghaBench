#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ count; scalar_t__ buffer; int sector; int offset; int /*<<< orphan*/ * file; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ BUFFER_SIZE ; 
 int /*<<< orphan*/  FALSE ; 
 int SECTOR_SIZE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__ cd ; 
 int /*<<< orphan*/  flush_buffer () ; 
 int fread (scalar_t__,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL write_from_file(FILE *file, DWORD size)
{
    if (cd.file != NULL)
    {
        int n;

        fseek(file, 0, SEEK_SET);
        while (size > 0)
        {
            n = BUFFER_SIZE - cd.count;
            if ((DWORD)n > size)
                n = size;

            if (fread(cd.buffer + cd.count, n, 1, file) < 1)
                return FALSE;

            cd.count += n;
            if (cd.count == BUFFER_SIZE)
                flush_buffer();
            cd.sector += n / SECTOR_SIZE;
            cd.offset += n % SECTOR_SIZE;
            size -= n;
        }
    }
    else
    {
        cd.sector += size / SECTOR_SIZE;
        cd.offset += size % SECTOR_SIZE;
    }

    return TRUE;
}