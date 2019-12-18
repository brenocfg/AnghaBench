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
struct chmUnitInfo {int flags; scalar_t__ length; char* path; } ;
struct chmPmglHeader {int block_next; int /*<<< orphan*/ * free_space; } ;
struct chmFile {size_t block_len; int index_head; scalar_t__ dir_offset; } ;
typedef  size_t UInt64 ;
typedef  int /*<<< orphan*/  UChar ;
typedef  int Int32 ;
typedef  int (* CHM_ENUMERATOR ) (struct chmFile*,struct chmUnitInfo*,void*) ;

/* Variables and functions */
 int CHM_ENUMERATE_DIRS ; 
 int CHM_ENUMERATE_FILES ; 
 int CHM_ENUMERATE_META ; 
 int CHM_ENUMERATE_NORMAL ; 
 int CHM_ENUMERATE_SPECIAL ; 
#define  CHM_ENUMERATOR_CONTINUE 130 
#define  CHM_ENUMERATOR_FAILURE 129 
#define  CHM_ENUMERATOR_SUCCESS 128 
 int CHM_MAX_PATHLEN ; 
 unsigned int _CHM_PMGL_LEN ; 
 size_t _chm_fetch_bytes (struct chmFile*,int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  _chm_parse_PMGL_entry (int /*<<< orphan*/ **,struct chmUnitInfo*) ; 
 int /*<<< orphan*/  _unmarshal_pmgl_header (int /*<<< orphan*/ **,unsigned int*,size_t,struct chmPmglHeader*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (unsigned int) ; 
 int strlen (char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int stub1 (struct chmFile*,struct chmUnitInfo*,void*) ; 

int chm_enumerate_dir(struct chmFile *h,
                      const char *prefix,
                      int what,
                      CHM_ENUMERATOR e,
                      void *context)
{
    /*
     * XXX: do this efficiently (i.e. using the tree index)
     */

    Int32 curPage;

    /* buffer to hold whatever page we're looking at */
    /* RWE 6/12/2003 */
    UChar *page_buf = malloc((unsigned int)h->block_len);
    struct chmPmglHeader header;
    UChar *end;
    UChar *cur;
    unsigned int lenRemain;

    /* set to 1 once we've started */
    int it_has_begun=0;

    /* the current ui */
    struct chmUnitInfo ui;
    int type_bits = (what & 0x7);
    int filter_bits = (what & 0xF8);
    UInt64 ui_path_len;

    /* the length of the prefix */
    char prefixRectified[CHM_MAX_PATHLEN+1];
    int prefixLen;
    char lastPath[CHM_MAX_PATHLEN+1];
    int lastPathLen;

    if (page_buf == NULL)
        return 0;

    /* starting page */
    curPage = h->index_head;

    /* initialize pathname state */
    strncpy(prefixRectified, prefix, CHM_MAX_PATHLEN);
    prefixRectified[CHM_MAX_PATHLEN] = '\0';
    prefixLen = strlen(prefixRectified);
    if (prefixLen != 0)
    {
        if (prefixRectified[prefixLen-1] != '/')
        {
            prefixRectified[prefixLen] = '/';
            prefixRectified[prefixLen+1] = '\0';
            ++prefixLen;
        }
    }
    lastPath[0] = '\0';
    lastPathLen = -1;

    /* until we have either returned or given up */
    while (curPage != -1)
    {

        /* try to fetch the index page */
        if (_chm_fetch_bytes(h,
                             page_buf,
                             (UInt64)h->dir_offset + (UInt64)curPage*h->block_len,
                             h->block_len) != h->block_len)
        {
            free(page_buf);
            return 0;
        }

        /* figure out start and end for this page */
        cur = page_buf;
        lenRemain = _CHM_PMGL_LEN;
        if (! _unmarshal_pmgl_header(&cur, &lenRemain, h->block_len, &header))
        {
            free(page_buf);
            return 0;
        }
        end = page_buf + h->block_len - (header.free_space);

        /* loop over this page */
        while (cur < end)
        {
            ui.flags = 0;

            if (! _chm_parse_PMGL_entry(&cur, &ui))
            {
                free(page_buf);
                return 0;
            }

            /* check if we should start */
            if (! it_has_begun)
            {
                if (ui.length == 0  &&  strncasecmp(ui.path, prefixRectified, prefixLen) == 0)
                    it_has_begun = 1;
                else
                    continue;

                if (ui.path[prefixLen] == '\0')
                    continue;
            }

            /* check if we should stop */
            else
            {
                if (strncasecmp(ui.path, prefixRectified, prefixLen) != 0)
                {
                    free(page_buf);
                    return 1;
                }
            }

            /* check if we should include this path */
            if (lastPathLen != -1)
            {
                if (strncasecmp(ui.path, lastPath, lastPathLen) == 0)
                    continue;
            }
            strncpy(lastPath, ui.path, CHM_MAX_PATHLEN);
            lastPath[CHM_MAX_PATHLEN] = '\0';
            lastPathLen = strlen(lastPath);

            /* get the length of the path */
            ui_path_len = strlen(ui.path)-1;

            /* check for DIRS */
            if (ui.path[ui_path_len] == '/')
                ui.flags |= CHM_ENUMERATE_DIRS;

            /* check for FILES */
            if (ui.path[ui_path_len] != '/')
                ui.flags |= CHM_ENUMERATE_FILES;

            /* check for NORMAL vs. META */
            if (ui.path[0] == '/')
            {

                /* check for NORMAL vs. SPECIAL */
                if (ui.path[1] == '#'  ||  ui.path[1] == '$')
                    ui.flags |= CHM_ENUMERATE_SPECIAL;
                else
                    ui.flags |= CHM_ENUMERATE_NORMAL;
            }
            else
                ui.flags |= CHM_ENUMERATE_META;

            if (! (type_bits & ui.flags))
                continue;

            if (filter_bits && ! (filter_bits & ui.flags))
                continue;

            /* call the enumerator */
            {
                int status = (*e)(h, &ui, context);
                switch (status)
                {
                    case CHM_ENUMERATOR_FAILURE:
                        free(page_buf);
                        return 0;
                    case CHM_ENUMERATOR_CONTINUE:
                        break;
                    case CHM_ENUMERATOR_SUCCESS:
                        free(page_buf);
                        return 1;
                    default:
                        break;
                }
            }
        }

        /* advance to next page */
        curPage = header.block_next;
    }

    free(page_buf);
    return 1;
}