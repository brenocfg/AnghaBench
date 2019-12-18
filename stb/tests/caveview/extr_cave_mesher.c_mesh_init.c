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

/* Variables and functions */
 size_t C_empty ; 
 void* SDL_CreateMutex () ; 
 int /*<<< orphan*/  STBVOX_GEOM_ceil_vheight_03 ; 
 int /*<<< orphan*/  STBVOX_GEOM_floor_vheight_12 ; 
 int /*<<< orphan*/  build_stair_rotations (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_wood_variations (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_wool_variations (int,int /*<<< orphan*/ ) ; 
 void* chunk_cache_mutex ; 
 void* chunk_get_mutex ; 
 int* effective_blocktype ; 
 int /*<<< orphan*/ * geom_map ; 
 int /*<<< orphan*/  memcpy (int*,size_t*,int) ; 
 int** minecraft_color_for_blocktype ; 
 int /*<<< orphan*/ * minecraft_geom_for_blocktype ; 
 size_t** minecraft_info ; 
 int** minecraft_tex1_for_blocktype ; 
 int* remap ; 
 int /*<<< orphan*/ * remap_data ; 
 int /*<<< orphan*/  remap_in_place (int,int) ; 

void mesh_init(void)
{
   int i;

   chunk_cache_mutex = SDL_CreateMutex();
   chunk_get_mutex   = SDL_CreateMutex();

   for (i=0; i < 256; ++i) {
      memcpy(minecraft_tex1_for_blocktype[i], minecraft_info[i]+1, 6);
      effective_blocktype[i] = (minecraft_info[i][0] == C_empty ? 0 : i);
      minecraft_geom_for_blocktype[i] = geom_map[minecraft_info[i][0]];
   }
   //effective_blocktype[50] = 0; // delete torches

   for (i=0; i < 6*256; ++i) {
      if (minecraft_tex1_for_blocktype[0][i] == 40)
         minecraft_color_for_blocktype[0][i] = 38 | 64; // apply to tex1
      if (minecraft_tex1_for_blocktype[0][i] == 39)
         minecraft_color_for_blocktype[0][i] = 39 | 64; // apply to tex1
      if (minecraft_tex1_for_blocktype[0][i] == 105)
         minecraft_color_for_blocktype[0][i] = 63; // emissive
      if (minecraft_tex1_for_blocktype[0][i] == 212)
         minecraft_color_for_blocktype[0][i] = 63; // emissive
      if (minecraft_tex1_for_blocktype[0][i] == 80)
         minecraft_color_for_blocktype[0][i] = 63; // emissive
   }

   for (i=0; i < 6; ++i) {
      minecraft_color_for_blocktype[172][i] = 47 | 64; // apply to tex1
      minecraft_color_for_blocktype[178][i] = 47 | 64; // apply to tex1
      minecraft_color_for_blocktype[18][i] = 39 | 64; // green
      minecraft_color_for_blocktype[161][i] = 37 | 64; // green
      minecraft_color_for_blocktype[10][i] = 63; // emissive lava
      minecraft_color_for_blocktype[11][i] = 63; // emissive
      //minecraft_color_for_blocktype[56][i] = 63; // emissive diamond
      minecraft_color_for_blocktype[48][i] = 63; // emissive dungeon
   }

   #ifdef VHEIGHT_TEST
   effective_blocktype[168] = 168;
   minecraft_tex1_for_blocktype[168][0] = 1;
   minecraft_tex1_for_blocktype[168][1] = 1;
   minecraft_tex1_for_blocktype[168][2] = 1;
   minecraft_tex1_for_blocktype[168][3] = 1;
   minecraft_tex1_for_blocktype[168][4] = 1;
   minecraft_tex1_for_blocktype[168][5] = 1;
   minecraft_geom_for_blocktype[168] = STBVOX_GEOM_floor_vheight_12;
   effective_blocktype[169] = 169;
   minecraft_tex1_for_blocktype[169][0] = 1;
   minecraft_tex1_for_blocktype[169][1] = 1;
   minecraft_tex1_for_blocktype[169][2] = 1;
   minecraft_tex1_for_blocktype[169][3] = 1;
   minecraft_tex1_for_blocktype[169][4] = 1;
   minecraft_tex1_for_blocktype[169][5] = 1;
   minecraft_geom_for_blocktype[169] = STBVOX_GEOM_ceil_vheight_03;
   #endif

   remap[53] = 1;
   remap[67] = 2;
   remap[108] = 3;
   remap[109] = 4;
   remap[114] = 5;
   remap[136] = 6;
   remap[156] = 7;
   for (i=0; i < 256; ++i)
      if (remap[i])
         build_stair_rotations(i, remap_data[remap[i]]);
   remap[35]  = 8;
   build_wool_variations(35, remap_data[remap[35]]);
   remap[5] = 11;
   build_wood_variations(5, remap_data[remap[5]]);

   // set the remap flags for these so they write the rotation values
   remap_in_place(54, 9);
   remap_in_place(146, 10);
}