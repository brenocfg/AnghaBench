#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int p; int mask; int slack; TYPE_1__** buckets; int /*<<< orphan*/  memory; } ;
struct TYPE_5__ {int hash; struct TYPE_5__* link; } ;
typedef  int FT_UFast ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  int FT_Long ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  TYPE_1__* FTC_Node ;
typedef  TYPE_2__* FTC_Cache ;

/* Variables and functions */
 int FTC_HASH_INITIAL_SIZE ; 
 scalar_t__ FTC_HASH_MAX_LOAD ; 
 int FTC_HASH_SUB_LOAD ; 
 scalar_t__ FT_RENEW_ARRAY (TYPE_1__**,int,int) ; 

__attribute__((used)) static void
  ftc_cache_resize( FTC_Cache  cache )
  {
    for (;;)
    {
      FTC_Node  node, *pnode;
      FT_UFast  p     = cache->p;
      FT_UFast  mask  = cache->mask;
      FT_UFast  count = mask + p + 1;    /* number of buckets */


      /* do we need to shrink the buckets array? */
      if ( cache->slack < 0 )
      {
        FTC_Node  new_list = NULL;


        /* try to expand the buckets array _before_ splitting
         * the bucket lists
         */
        if ( p >= mask )
        {
          FT_Memory  memory = cache->memory;
          FT_Error   error;


          /* if we can't expand the array, leave immediately */
          if ( FT_RENEW_ARRAY( cache->buckets,
                               ( mask + 1 ) * 2, ( mask + 1 ) * 4 ) )
            break;
        }

        /* split a single bucket */
        pnode = cache->buckets + p;

        for (;;)
        {
          node = *pnode;
          if ( !node )
            break;

          if ( node->hash & ( mask + 1 ) )
          {
            *pnode     = node->link;
            node->link = new_list;
            new_list   = node;
          }
          else
            pnode = &node->link;
        }

        cache->buckets[p + mask + 1] = new_list;

        cache->slack += FTC_HASH_MAX_LOAD;

        if ( p >= mask )
        {
          cache->mask = 2 * mask + 1;
          cache->p    = 0;
        }
        else
          cache->p = p + 1;
      }

      /* do we need to expand the buckets array? */
      else if ( cache->slack > (FT_Long)count * FTC_HASH_SUB_LOAD )
      {
        FT_UFast   old_index = p + mask;
        FTC_Node*  pold;


        if ( old_index + 1 <= FTC_HASH_INITIAL_SIZE )
          break;

        if ( p == 0 )
        {
          FT_Memory  memory = cache->memory;
          FT_Error   error;


          /* if we can't shrink the array, leave immediately */
          if ( FT_RENEW_ARRAY( cache->buckets,
                               ( mask + 1 ) * 2, mask + 1 ) )
            break;

          cache->mask >>= 1;
          p             = cache->mask;
        }
        else
          p--;

        pnode = cache->buckets + p;
        while ( *pnode )
          pnode = &(*pnode)->link;

        pold   = cache->buckets + old_index;
        *pnode = *pold;
        *pold  = NULL;

        cache->slack -= FTC_HASH_MAX_LOAD;
        cache->p      = p;
      }

      /* otherwise, the hash table is balanced */
      else
        break;
    }
  }