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
struct _cms_io_handler {struct _cms_io_handler* Block; scalar_t__ FreeBlockOnClose; scalar_t__ stream; } ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
typedef  struct _cms_io_handler FILEMEM ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,struct _cms_io_handler*) ; 

__attribute__((used)) static
cmsBool  MemoryClose(cmsContext ContextID, struct _cms_io_handler* iohandler)
{
    FILEMEM* ResData = (FILEMEM*) iohandler ->stream;

    if (ResData ->FreeBlockOnClose) {

        if (ResData ->Block) _cmsFree(ContextID, ResData ->Block);
    }

    _cmsFree(ContextID, ResData);
    _cmsFree(ContextID, iohandler);

    return TRUE;
}