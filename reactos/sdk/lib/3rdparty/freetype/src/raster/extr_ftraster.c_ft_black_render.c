#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct TYPE_11__* sizeBuff; struct TYPE_11__* buff; } ;
typedef  TYPE_1__ black_TWorker ;
struct TYPE_15__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  rows; int /*<<< orphan*/  width; } ;
struct TYPE_14__ {scalar_t__ n_points; int n_contours; scalar_t__* contours; TYPE_3__* points; } ;
struct TYPE_16__ {TYPE_6__ target; TYPE_5__ outline; } ;
struct TYPE_13__ {int flags; TYPE_6__* target; scalar_t__ source; } ;
struct TYPE_12__ {int x; int y; } ;
typedef  TYPE_1__ Long ;
typedef  TYPE_3__ FT_Vector ;
typedef  TYPE_4__ FT_Raster_Params ;
typedef  int /*<<< orphan*/  FT_Raster ;
typedef  TYPE_5__ FT_Outline ;
typedef  int FT_Error ;
typedef  TYPE_6__ FT_Bitmap ;

/* Variables and functions */
 int FT_MAX (int /*<<< orphan*/ ,int) ; 
 int FT_MAX_BLACK_POOL ; 
 int FT_RASTER_FLAG_AA ; 
 int FT_RASTER_FLAG_DIRECT ; 
 int /*<<< orphan*/  FT_RENDER_POOL_SIZE ; 
 int FT_THROW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Invalid ; 
 int /*<<< orphan*/  Not_Ini ; 
 int /*<<< orphan*/  Out_Of_Memory ; 
 int /*<<< orphan*/  RAS_VAR ; 
 int Raster_Err_None ; 
 int Render_Glyph (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unsupported ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 TYPE_7__ ras ; 

__attribute__((used)) static int
  ft_black_render( FT_Raster                raster,
                   const FT_Raster_Params*  params )
  {
    const FT_Outline*  outline    = (const FT_Outline*)params->source;
    const FT_Bitmap*   target_map = params->target;

#ifdef __REACTOS__
    FT_Error ret;
    black_TWorker *worker;
    Long *buffer;
#else
    black_TWorker  worker[1];

    Long  buffer[FT_MAX_BLACK_POOL];
#endif


    if ( !raster )
      return FT_THROW( Not_Ini );

    if ( !outline )
      return FT_THROW( Invalid );

    /* return immediately if the outline is empty */
    if ( outline->n_points == 0 || outline->n_contours <= 0 )
      return Raster_Err_None;

    if ( !outline->contours || !outline->points )
      return FT_THROW( Invalid );

    if ( outline->n_points !=
           outline->contours[outline->n_contours - 1] + 1 )
      return FT_THROW( Invalid );

    /* this version of the raster does not support direct rendering, sorry */
    if ( params->flags & FT_RASTER_FLAG_DIRECT )
      return FT_THROW( Unsupported );

    if ( params->flags & FT_RASTER_FLAG_AA )
      return FT_THROW( Unsupported );

    if ( !target_map )
      return FT_THROW( Invalid );

    /* nothing to do */
    if ( !target_map->width || !target_map->rows )
      return Raster_Err_None;

    if ( !target_map->buffer )
      return FT_THROW( Invalid );

    /* reject too large outline coordinates */
    {
      FT_Vector*  vec   = outline->points;
      FT_Vector*  limit = vec + outline->n_points;


      for ( ; vec < limit; vec++ )
      {
        if ( vec->x < -0x1000000L || vec->x > 0x1000000L ||
             vec->y < -0x1000000L || vec->y > 0x1000000L )
         return FT_THROW( Invalid );
      }
    }

#ifdef __REACTOS__
    worker = malloc(sizeof(black_TWorker));
    buffer = malloc(FT_MAX(FT_RENDER_POOL_SIZE, 2048));
    if (!worker || !buffer)
    {
      free(worker);
      free(buffer);
      return FT_THROW( Out_Of_Memory );
    }
#endif

    ras.outline = *outline;
    ras.target  = *target_map;

    worker->buff     = buffer;
#ifdef __REACTOS__
    worker->sizeBuff = buffer + FT_MAX_BLACK_POOL;
#else
    worker->sizeBuff = (&buffer)[1]; /* Points to right after buffer. */
#endif

#ifdef __REACTOS__
    ret = Render_Glyph(RAS_VAR);
    free(worker);
    free(buffer);
    return ret;
#else
    return Render_Glyph( RAS_VAR );
#endif
  }