#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {size_t nb_children; TYPE_2__* root; struct TYPE_12__** children; scalar_t__ binary; TYPE_1__* ptarget; scalar_t__ pos_data; scalar_t__ size; } ;
typedef  TYPE_3__ xobject ;
struct TYPE_13__ {int nb_pxo_globals; TYPE_3__* pxo; int /*<<< orphan*/  level; scalar_t__ value; TYPE_3__* pxo_tab; TYPE_1__** pxo_globals; scalar_t__ cur_pos_data; } ;
typedef  TYPE_4__ parse_buffer ;
typedef  int ULONG ;
struct TYPE_11__ {scalar_t__ nb_subobjects; } ;
struct TYPE_10__ {int nb_subobjects; int /*<<< orphan*/  name; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,char*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 size_t MAX_CHILDREN ; 
 scalar_t__ MAX_SUBOBJECTS ; 
 scalar_t__ TOKEN_CBRACE ; 
 scalar_t__ TOKEN_NAME ; 
 scalar_t__ TOKEN_OBRACE ; 
 int /*<<< orphan*/  TRACE (char*,char*) ; 
 scalar_t__ TRUE ; 
 scalar_t__ check_TOKEN (TYPE_4__*) ; 
 scalar_t__ get_TOKEN (TYPE_4__*) ; 
 int /*<<< orphan*/  parse_object (TYPE_4__*) ; 
 int /*<<< orphan*/  parse_object_members_list (TYPE_4__*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static BOOL parse_object_parts(parse_buffer * buf, BOOL allow_optional)
{
  buf->pxo->nb_children = 0;

  if (!parse_object_members_list(buf))
    return FALSE;

  if (allow_optional)
  {
    buf->pxo->size = buf->cur_pos_data - buf->pxo->pos_data;

    while (1)
    {
      if (check_TOKEN(buf) == TOKEN_OBRACE)
      {
        ULONG i, j;
        get_TOKEN(buf);
        if (get_TOKEN(buf) != TOKEN_NAME)
          return FALSE;
        if (get_TOKEN(buf) != TOKEN_CBRACE)
          return FALSE;
        TRACE("Found optional reference %s\n", (char*)buf->value);
        for (i = 0; i < (buf->nb_pxo_globals+1); i++)
        {
          for (j = 0; j < (buf->pxo_globals[i])[0].nb_subobjects; j++)
          {
            if (!strcmp((buf->pxo_globals[i])[j].name, (char*)buf->value))
              goto _exit;
          }
        }
_exit:
        if (i == (buf->nb_pxo_globals+1))
        {
          ERR("Reference to unknown object %s\n", (char*)buf->value);
          return FALSE;
        }

        if (buf->pxo->root->nb_subobjects >= MAX_SUBOBJECTS)
        {
            FIXME("Too many sub-objects\n");
            return FALSE;
        }

        buf->pxo->children[buf->pxo->nb_children] = &buf->pxo_tab[buf->pxo->root->nb_subobjects++];
        buf->pxo->children[buf->pxo->nb_children]->ptarget = &(buf->pxo_globals[i])[j];
        buf->pxo->children[buf->pxo->nb_children]->binary = FALSE;
        buf->pxo->nb_children++;
      }
      else if (check_TOKEN(buf) == TOKEN_NAME)
      {
        xobject* pxo = buf->pxo;

        if (buf->pxo->root->nb_subobjects >= MAX_SUBOBJECTS)
        {
            FIXME("Too many sub-objects\n");
            return FALSE;
        }

        buf->pxo = buf->pxo->children[buf->pxo->nb_children] = &buf->pxo_tab[buf->pxo->root->nb_subobjects];
        pxo->root->nb_subobjects++;

        TRACE("Enter optional %s\n", (char*)buf->value);
        buf->level++;
        if (!parse_object(buf))
        {
          buf->level--;
          return FALSE;
        }
        buf->level--;
        buf->pxo = pxo;
        buf->pxo->nb_children++;
      }
      else
        break;
    }
  }

  if (buf->pxo->nb_children > MAX_CHILDREN)
  {
    FIXME("Too many children %d\n", buf->pxo->nb_children);
    return FALSE;
  }

  return TRUE;
}