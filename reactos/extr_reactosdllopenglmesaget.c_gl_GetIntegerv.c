#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_61__   TYPE_9__ ;
typedef  struct TYPE_60__   TYPE_8__ ;
typedef  struct TYPE_59__   TYPE_7__ ;
typedef  struct TYPE_58__   TYPE_6__ ;
typedef  struct TYPE_57__   TYPE_5__ ;
typedef  struct TYPE_56__   TYPE_4__ ;
typedef  struct TYPE_55__   TYPE_3__ ;
typedef  struct TYPE_54__   TYPE_2__ ;
typedef  struct TYPE_53__   TYPE_29__ ;
typedef  struct TYPE_52__   TYPE_28__ ;
typedef  struct TYPE_51__   TYPE_27__ ;
typedef  struct TYPE_50__   TYPE_26__ ;
typedef  struct TYPE_49__   TYPE_25__ ;
typedef  struct TYPE_48__   TYPE_24__ ;
typedef  struct TYPE_47__   TYPE_23__ ;
typedef  struct TYPE_46__   TYPE_22__ ;
typedef  struct TYPE_45__   TYPE_21__ ;
typedef  struct TYPE_44__   TYPE_20__ ;
typedef  struct TYPE_43__   TYPE_1__ ;
typedef  struct TYPE_42__   TYPE_19__ ;
typedef  struct TYPE_41__   TYPE_18__ ;
typedef  struct TYPE_40__   TYPE_17__ ;
typedef  struct TYPE_39__   TYPE_16__ ;
typedef  struct TYPE_38__   TYPE_15__ ;
typedef  struct TYPE_37__   TYPE_14__ ;
typedef  struct TYPE_36__   TYPE_13__ ;
typedef  struct TYPE_35__   TYPE_12__ ;
typedef  struct TYPE_34__   TYPE_11__ ;
typedef  struct TYPE_33__   TYPE_10__ ;

/* Type definitions */
struct TYPE_61__ {int /*<<< orphan*/  ListBase; } ;
struct TYPE_60__ {int /*<<< orphan*/  Width; int /*<<< orphan*/  StippleFactor; int /*<<< orphan*/  StipplePattern; int /*<<< orphan*/  StippleFlag; int /*<<< orphan*/  SmoothFlag; } ;
struct TYPE_59__ {int* Ambient; int /*<<< orphan*/  TwoSide; int /*<<< orphan*/  LocalViewer; } ;
struct TYPE_58__ {int /*<<< orphan*/  Enabled; } ;
struct TYPE_57__ {int* Color; int /*<<< orphan*/  Start; int /*<<< orphan*/  Mode; int /*<<< orphan*/  Index; int /*<<< orphan*/  End; int /*<<< orphan*/  Density; int /*<<< orphan*/  Enabled; } ;
struct TYPE_56__ {size_t BufferSize; size_t Type; } ;
struct TYPE_55__ {int* ByteColor; int* Normal; int* RasterColor; int /*<<< orphan*/  EdgeFlag; int /*<<< orphan*/ * TexCoord; int /*<<< orphan*/  RasterPosValid; int /*<<< orphan*/ * RasterTexCoord; int /*<<< orphan*/ * RasterPos; int /*<<< orphan*/  RasterIndex; int /*<<< orphan*/  RasterDistance; int /*<<< orphan*/  Index; } ;
struct TYPE_54__ {int /*<<< orphan*/  Mask; int /*<<< orphan*/  Test; int /*<<< orphan*/  Func; int /*<<< orphan*/  Clear; } ;
struct TYPE_52__ {int Enabled; int* EnvColor; int TexGenEnabled; TYPE_27__* Current2D; TYPE_26__* Current1D; int /*<<< orphan*/  EnvMode; } ;
struct TYPE_49__ {size_t VertexSize; size_t VertexType; size_t VertexStride; size_t NormalType; size_t NormalStride; size_t ColorSize; size_t ColorType; size_t ColorStride; size_t IndexType; size_t IndexStride; size_t TexCoordSize; size_t TexCoordType; size_t TexCoordStride; size_t EdgeFlagStride; } ;
struct TYPE_48__ {size_t IndexOffset; size_t IndexShift; size_t MapAtoAsize; size_t MapBtoBsize; size_t MapGtoGsize; size_t MapItoAsize; size_t MapItoBsize; size_t MapItoGsize; size_t MapItoIsize; size_t MapItoRsize; size_t MapRtoRsize; size_t MapStoSsize; int /*<<< orphan*/  ZoomY; int /*<<< orphan*/  ZoomX; int /*<<< orphan*/  RedScale; int /*<<< orphan*/  RedBias; int /*<<< orphan*/  ReadBuffer; int /*<<< orphan*/  MapStencilFlag; int /*<<< orphan*/  MapColorFlag; int /*<<< orphan*/  GreenScale; int /*<<< orphan*/  GreenBias; int /*<<< orphan*/  DepthScale; int /*<<< orphan*/  DepthBias; int /*<<< orphan*/  BlueScale; int /*<<< orphan*/  BlueBias; int /*<<< orphan*/  AlphaScale; int /*<<< orphan*/  AlphaBias; } ;
struct TYPE_47__ {int /*<<< orphan*/  Height; int /*<<< orphan*/  Width; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; int /*<<< orphan*/  Far; int /*<<< orphan*/  Near; } ;
struct TYPE_46__ {size_t Alignment; size_t RowLength; size_t SkipPixels; size_t SkipRows; int /*<<< orphan*/  SwapBytes; int /*<<< orphan*/  LsbFirst; } ;
struct TYPE_45__ {int /*<<< orphan*/  WriteMask; int /*<<< orphan*/  ValueMask; int /*<<< orphan*/  Enabled; int /*<<< orphan*/  Ref; int /*<<< orphan*/  ZPassFunc; int /*<<< orphan*/  ZFailFunc; int /*<<< orphan*/  Function; int /*<<< orphan*/  FailFunc; int /*<<< orphan*/  Clear; } ;
struct TYPE_42__ {int /*<<< orphan*/  ShadeModel; TYPE_7__ Model; int /*<<< orphan*/  Enabled; TYPE_6__* Light; int /*<<< orphan*/  ColorMaterialMode; int /*<<< orphan*/  ColorMaterialFace; int /*<<< orphan*/  ColorMaterialEnabled; } ;
struct TYPE_41__ {int /*<<< orphan*/  Enabled; int /*<<< orphan*/  Height; int /*<<< orphan*/  Width; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
struct TYPE_40__ {int /*<<< orphan*/  PolygonSmooth; int /*<<< orphan*/  PointSmooth; int /*<<< orphan*/  PerspectiveCorrection; int /*<<< orphan*/  LineSmooth; int /*<<< orphan*/  Fog; } ;
struct TYPE_39__ {int /*<<< orphan*/  SmoothFlag; int /*<<< orphan*/  OffsetUnits; int /*<<< orphan*/  OffsetFactor; int /*<<< orphan*/  BackMode; int /*<<< orphan*/  FrontMode; int /*<<< orphan*/  FrontFace; int /*<<< orphan*/  CullFaceMode; int /*<<< orphan*/  CullFlag; } ;
struct TYPE_38__ {int /*<<< orphan*/  SmoothFlag; int /*<<< orphan*/  Size; } ;
struct TYPE_37__ {size_t Alignment; size_t RowLength; size_t SkipPixels; size_t SkipRows; int /*<<< orphan*/  SwapBytes; int /*<<< orphan*/  LsbFirst; } ;
struct TYPE_36__ {int /*<<< orphan*/  Normalize; int /*<<< orphan*/  MatrixMode; int /*<<< orphan*/ * ClipEnabled; } ;
struct TYPE_35__ {int /*<<< orphan*/  NameStackDepth; } ;
struct TYPE_34__ {int /*<<< orphan*/  Map2Vertex4; int /*<<< orphan*/  Map2Vertex3; int /*<<< orphan*/  Map2TextureCoord4; int /*<<< orphan*/  Map2TextureCoord3; int /*<<< orphan*/  Map2TextureCoord2; int /*<<< orphan*/  Map2TextureCoord1; int /*<<< orphan*/  Map2Normal; int /*<<< orphan*/  Map2Index; int /*<<< orphan*/  MapGrid2vn; int /*<<< orphan*/  MapGrid2un; int /*<<< orphan*/  MapGrid2v2; int /*<<< orphan*/  MapGrid2v1; int /*<<< orphan*/  MapGrid2u2; int /*<<< orphan*/  MapGrid2u1; int /*<<< orphan*/  Map2Color4; int /*<<< orphan*/  Map1Vertex4; int /*<<< orphan*/  Map1Vertex3; int /*<<< orphan*/  Map1TextureCoord4; int /*<<< orphan*/  Map1TextureCoord3; int /*<<< orphan*/  Map1TextureCoord2; int /*<<< orphan*/  Map1TextureCoord1; int /*<<< orphan*/  Map1Normal; int /*<<< orphan*/  Map1Index; int /*<<< orphan*/  MapGrid1un; int /*<<< orphan*/  MapGrid1u2; int /*<<< orphan*/  MapGrid1u1; int /*<<< orphan*/  Map1Color4; int /*<<< orphan*/  AutoNormal; } ;
struct TYPE_33__ {int AlphaRef; int* ClearColor; int ColorMask; int /*<<< orphan*/  LogicOp; int /*<<< orphan*/  ColorLogicOpEnabled; int /*<<< orphan*/  IndexLogicOpEnabled; int /*<<< orphan*/  IndexMask; int /*<<< orphan*/  ClearIndex; int /*<<< orphan*/  DrawBuffer; int /*<<< orphan*/  DitherFlag; int /*<<< orphan*/  BlendSrc; int /*<<< orphan*/  BlendDst; int /*<<< orphan*/  BlendEnabled; int /*<<< orphan*/  AlphaFunc; int /*<<< orphan*/  AlphaEnabled; } ;
struct TYPE_43__ {int* ClearColor; } ;
struct TYPE_53__ {size_t ClientAttribStackDepth; TYPE_28__ Texture; TYPE_25__ Array; TYPE_24__ Pixel; TYPE_23__ Viewport; TYPE_22__ Unpack; int /*<<< orphan*/  TextureStackDepth; int /*<<< orphan*/ * TextureMatrix; TYPE_21__ Stencil; TYPE_20__* Visual; TYPE_19__ Light; TYPE_18__ Scissor; int /*<<< orphan*/  RenderMode; int /*<<< orphan*/  ProjectionStackDepth; int /*<<< orphan*/ * ProjectionMatrix; int /*<<< orphan*/ * PolygonStipple; TYPE_17__ Hint; TYPE_16__ Polygon; TYPE_15__ Point; TYPE_14__ Pack; TYPE_13__ Transform; TYPE_12__ Select; int /*<<< orphan*/  ModelViewStackDepth; int /*<<< orphan*/ * ModelViewMatrix; TYPE_11__ Eval; TYPE_10__ Color; int /*<<< orphan*/  ExecuteFlag; int /*<<< orphan*/  CurrentListNum; TYPE_9__ List; TYPE_8__ Line; TYPE_5__ Fog; TYPE_4__ Feedback; TYPE_3__ Current; TYPE_2__ Depth; int /*<<< orphan*/  AttribStackDepth; TYPE_1__ Accum; } ;
struct TYPE_51__ {size_t Name; } ;
struct TYPE_50__ {size_t Name; } ;
struct TYPE_44__ {size_t AlphaBits; int InvRedScale; int InvGreenScale; int InvBlueScale; int InvAlphaScale; size_t DepthBits; size_t StencilBits; int /*<<< orphan*/  RGBAflag; int /*<<< orphan*/  RedBits; int /*<<< orphan*/  IndexBits; int /*<<< orphan*/  GreenBits; int /*<<< orphan*/  DBflag; int /*<<< orphan*/  BlueBits; int /*<<< orphan*/  AccumBits; } ;
typedef  size_t GLuint ;
typedef  size_t GLint ;
typedef  int GLenum ;
typedef  TYPE_29__ GLcontext ;

/* Variables and functions */
 size_t FLOAT_TO_INT (int) ; 
#define  GL_ACCUM_ALPHA_BITS 363 
#define  GL_ACCUM_BLUE_BITS 362 
#define  GL_ACCUM_CLEAR_VALUE 361 
#define  GL_ACCUM_GREEN_BITS 360 
#define  GL_ACCUM_RED_BITS 359 
#define  GL_ALPHA_BIAS 358 
#define  GL_ALPHA_BITS 357 
#define  GL_ALPHA_SCALE 356 
#define  GL_ALPHA_TEST 355 
#define  GL_ALPHA_TEST_FUNC 354 
#define  GL_ALPHA_TEST_REF 353 
#define  GL_ATTRIB_STACK_DEPTH 352 
#define  GL_AUTO_NORMAL 351 
#define  GL_AUX_BUFFERS 350 
#define  GL_BLEND 349 
#define  GL_BLEND_DST 348 
#define  GL_BLEND_SRC 347 
#define  GL_BLUE_BIAS 346 
#define  GL_BLUE_BITS 345 
#define  GL_BLUE_SCALE 344 
#define  GL_CLIENT_ATTRIB_STACK_DEPTH 343 
#define  GL_CLIP_PLANE0 342 
#define  GL_CLIP_PLANE1 341 
#define  GL_CLIP_PLANE2 340 
#define  GL_CLIP_PLANE3 339 
#define  GL_CLIP_PLANE4 338 
#define  GL_CLIP_PLANE5 337 
#define  GL_COLOR_ARRAY_COUNT_EXT 336 
#define  GL_COLOR_ARRAY_SIZE 335 
#define  GL_COLOR_ARRAY_STRIDE 334 
#define  GL_COLOR_ARRAY_TYPE 333 
#define  GL_COLOR_CLEAR_VALUE 332 
#define  GL_COLOR_LOGIC_OP 331 
#define  GL_COLOR_MATERIAL 330 
#define  GL_COLOR_MATERIAL_FACE 329 
#define  GL_COLOR_MATERIAL_PARAMETER 328 
#define  GL_COLOR_WRITEMASK 327 
 int /*<<< orphan*/  GL_COMPILE ; 
 int /*<<< orphan*/  GL_COMPILE_AND_EXECUTE ; 
#define  GL_CULL_FACE 326 
#define  GL_CULL_FACE_MODE 325 
#define  GL_CURRENT_COLOR 324 
#define  GL_CURRENT_INDEX 323 
#define  GL_CURRENT_NORMAL 322 
#define  GL_CURRENT_RASTER_COLOR 321 
#define  GL_CURRENT_RASTER_DISTANCE 320 
#define  GL_CURRENT_RASTER_INDEX 319 
#define  GL_CURRENT_RASTER_POSITION 318 
#define  GL_CURRENT_RASTER_POSITION_VALID 317 
#define  GL_CURRENT_RASTER_TEXTURE_COORDS 316 
#define  GL_CURRENT_TEXTURE_COORDS 315 
#define  GL_DEPTH_BIAS 314 
#define  GL_DEPTH_BITS 313 
#define  GL_DEPTH_CLEAR_VALUE 312 
#define  GL_DEPTH_FUNC 311 
#define  GL_DEPTH_RANGE 310 
#define  GL_DEPTH_SCALE 309 
#define  GL_DEPTH_TEST 308 
#define  GL_DEPTH_WRITEMASK 307 
#define  GL_DITHER 306 
#define  GL_DOUBLEBUFFER 305 
#define  GL_DRAW_BUFFER 304 
#define  GL_EDGE_FLAG 303 
#define  GL_EDGE_FLAG_ARRAY_COUNT_EXT 302 
#define  GL_EDGE_FLAG_ARRAY_STRIDE 301 
#define  GL_FEEDBACK_BUFFER_SIZE 300 
#define  GL_FEEDBACK_BUFFER_TYPE 299 
#define  GL_FOG 298 
#define  GL_FOG_COLOR 297 
#define  GL_FOG_DENSITY 296 
#define  GL_FOG_END 295 
#define  GL_FOG_HINT 294 
#define  GL_FOG_INDEX 293 
#define  GL_FOG_MODE 292 
#define  GL_FOG_START 291 
#define  GL_FRONT_FACE 290 
#define  GL_GREEN_BIAS 289 
#define  GL_GREEN_BITS 288 
#define  GL_GREEN_SCALE 287 
#define  GL_INDEX_ARRAY_COUNT_EXT 286 
#define  GL_INDEX_ARRAY_STRIDE 285 
#define  GL_INDEX_ARRAY_TYPE 284 
#define  GL_INDEX_BITS 283 
#define  GL_INDEX_CLEAR_VALUE 282 
#define  GL_INDEX_LOGIC_OP 281 
#define  GL_INDEX_MODE 280 
#define  GL_INDEX_OFFSET 279 
#define  GL_INDEX_SHIFT 278 
#define  GL_INDEX_WRITEMASK 277 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
#define  GL_LIGHT0 276 
#define  GL_LIGHT1 275 
#define  GL_LIGHT2 274 
#define  GL_LIGHT3 273 
#define  GL_LIGHT4 272 
#define  GL_LIGHT5 271 
#define  GL_LIGHT6 270 
#define  GL_LIGHT7 269 
#define  GL_LIGHTING 268 
#define  GL_LIGHT_MODEL_AMBIENT 267 
#define  GL_LIGHT_MODEL_LOCAL_VIEWER 266 
#define  GL_LIGHT_MODEL_TWO_SIDE 265 
#define  GL_LINE_SMOOTH 264 
#define  GL_LINE_SMOOTH_HINT 263 
#define  GL_LINE_STIPPLE 262 
#define  GL_LINE_STIPPLE_PATTERN 261 
#define  GL_LINE_STIPPLE_REPEAT 260 
#define  GL_LINE_WIDTH 259 
#define  GL_LINE_WIDTH_GRANULARITY 258 
#define  GL_LINE_WIDTH_RANGE 257 
#define  GL_LIST_BASE 256 
#define  GL_LIST_INDEX 255 
#define  GL_LIST_MODE 254 
#define  GL_LOGIC_OP_MODE 253 
#define  GL_MAP1_COLOR_4 252 
#define  GL_MAP1_GRID_DOMAIN 251 
#define  GL_MAP1_GRID_SEGMENTS 250 
#define  GL_MAP1_INDEX 249 
#define  GL_MAP1_NORMAL 248 
#define  GL_MAP1_TEXTURE_COORD_1 247 
#define  GL_MAP1_TEXTURE_COORD_2 246 
#define  GL_MAP1_TEXTURE_COORD_3 245 
#define  GL_MAP1_TEXTURE_COORD_4 244 
#define  GL_MAP1_VERTEX_3 243 
#define  GL_MAP1_VERTEX_4 242 
#define  GL_MAP2_COLOR_4 241 
#define  GL_MAP2_GRID_DOMAIN 240 
#define  GL_MAP2_GRID_SEGMENTS 239 
#define  GL_MAP2_INDEX 238 
#define  GL_MAP2_NORMAL 237 
#define  GL_MAP2_TEXTURE_COORD_1 236 
#define  GL_MAP2_TEXTURE_COORD_2 235 
#define  GL_MAP2_TEXTURE_COORD_3 234 
#define  GL_MAP2_TEXTURE_COORD_4 233 
#define  GL_MAP2_VERTEX_3 232 
#define  GL_MAP2_VERTEX_4 231 
#define  GL_MAP_COLOR 230 
#define  GL_MAP_STENCIL 229 
#define  GL_MATRIX_MODE 228 
#define  GL_MAX_ATTRIB_STACK_DEPTH 227 
#define  GL_MAX_CLIENT_ATTRIB_STACK_DEPTH 226 
#define  GL_MAX_CLIP_PLANES 225 
#define  GL_MAX_EVAL_ORDER 224 
#define  GL_MAX_LIGHTS 223 
#define  GL_MAX_LIST_NESTING 222 
#define  GL_MAX_MODELVIEW_STACK_DEPTH 221 
#define  GL_MAX_NAME_STACK_DEPTH 220 
#define  GL_MAX_PIXEL_MAP_TABLE 219 
#define  GL_MAX_PROJECTION_STACK_DEPTH 218 
#define  GL_MAX_TEXTURE_SIZE 217 
#define  GL_MAX_TEXTURE_STACK_DEPTH 216 
#define  GL_MAX_VIEWPORT_DIMS 215 
#define  GL_MODELVIEW_MATRIX 214 
#define  GL_MODELVIEW_STACK_DEPTH 213 
#define  GL_NAME_STACK_DEPTH 212 
#define  GL_NORMALIZE 211 
#define  GL_NORMAL_ARRAY_COUNT_EXT 210 
#define  GL_NORMAL_ARRAY_STRIDE 209 
#define  GL_NORMAL_ARRAY_TYPE 208 
#define  GL_PACK_ALIGNMENT 207 
#define  GL_PACK_LSB_FIRST 206 
#define  GL_PACK_ROW_LENGTH 205 
#define  GL_PACK_SKIP_PIXELS 204 
#define  GL_PACK_SKIP_ROWS 203 
#define  GL_PACK_SWAP_BYTES 202 
#define  GL_PERSPECTIVE_CORRECTION_HINT 201 
#define  GL_PIXEL_MAP_A_TO_A_SIZE 200 
#define  GL_PIXEL_MAP_B_TO_B_SIZE 199 
#define  GL_PIXEL_MAP_G_TO_G_SIZE 198 
#define  GL_PIXEL_MAP_I_TO_A_SIZE 197 
#define  GL_PIXEL_MAP_I_TO_B_SIZE 196 
#define  GL_PIXEL_MAP_I_TO_G_SIZE 195 
#define  GL_PIXEL_MAP_I_TO_I_SIZE 194 
#define  GL_PIXEL_MAP_I_TO_R_SIZE 193 
#define  GL_PIXEL_MAP_R_TO_R_SIZE 192 
#define  GL_PIXEL_MAP_S_TO_S_SIZE 191 
#define  GL_POINT_SIZE 190 
#define  GL_POINT_SIZE_GRANULARITY 189 
#define  GL_POINT_SIZE_RANGE 188 
#define  GL_POINT_SMOOTH 187 
#define  GL_POINT_SMOOTH_HINT 186 
#define  GL_POLYGON_MODE 185 
#define  GL_POLYGON_OFFSET_FACTOR 184 
#define  GL_POLYGON_OFFSET_UNITS 183 
#define  GL_POLYGON_SMOOTH 182 
#define  GL_POLYGON_SMOOTH_HINT 181 
#define  GL_POLYGON_STIPPLE 180 
#define  GL_PROJECTION_MATRIX 179 
#define  GL_PROJECTION_STACK_DEPTH 178 
#define  GL_READ_BUFFER 177 
#define  GL_RED_BIAS 176 
#define  GL_RED_BITS 175 
#define  GL_RED_SCALE 174 
#define  GL_RENDER_MODE 173 
#define  GL_RGBA_MODE 172 
#define  GL_SCISSOR_BOX 171 
#define  GL_SCISSOR_TEST 170 
#define  GL_SHADE_MODEL 169 
#define  GL_STENCIL_BITS 168 
#define  GL_STENCIL_CLEAR_VALUE 167 
#define  GL_STENCIL_FAIL 166 
#define  GL_STENCIL_FUNC 165 
#define  GL_STENCIL_PASS_DEPTH_FAIL 164 
#define  GL_STENCIL_PASS_DEPTH_PASS 163 
#define  GL_STENCIL_REF 162 
#define  GL_STENCIL_TEST 161 
#define  GL_STENCIL_VALUE_MASK 160 
#define  GL_STENCIL_WRITEMASK 159 
#define  GL_STEREO 158 
#define  GL_SUBPIXEL_BITS 157 
#define  GL_TEXTURE_1D 156 
#define  GL_TEXTURE_2D 155 
#define  GL_TEXTURE_BINDING_1D 154 
#define  GL_TEXTURE_BINDING_2D 153 
#define  GL_TEXTURE_COORD_ARRAY_COUNT_EXT 152 
#define  GL_TEXTURE_COORD_ARRAY_SIZE 151 
#define  GL_TEXTURE_COORD_ARRAY_STRIDE 150 
#define  GL_TEXTURE_COORD_ARRAY_TYPE 149 
#define  GL_TEXTURE_ENV_COLOR 148 
#define  GL_TEXTURE_ENV_MODE 147 
#define  GL_TEXTURE_GEN_Q 146 
#define  GL_TEXTURE_GEN_R 145 
#define  GL_TEXTURE_GEN_S 144 
#define  GL_TEXTURE_GEN_T 143 
#define  GL_TEXTURE_MATRIX 142 
#define  GL_TEXTURE_STACK_DEPTH 141 
#define  GL_UNPACK_ALIGNMENT 140 
#define  GL_UNPACK_LSB_FIRST 139 
#define  GL_UNPACK_ROW_LENGTH 138 
#define  GL_UNPACK_SKIP_PIXELS 137 
#define  GL_UNPACK_SKIP_ROWS 136 
#define  GL_UNPACK_SWAP_BYTES 135 
#define  GL_VERTEX_ARRAY_COUNT_EXT 134 
#define  GL_VERTEX_ARRAY_SIZE 133 
#define  GL_VERTEX_ARRAY_STRIDE 132 
#define  GL_VERTEX_ARRAY_TYPE 131 
#define  GL_VIEWPORT 130 
#define  GL_ZOOM_X 129 
#define  GL_ZOOM_Y 128 
 scalar_t__ INSIDE_BEGIN_END (TYPE_29__*) ; 
 int /*<<< orphan*/  LINE_WIDTH_GRANULARITY ; 
 int /*<<< orphan*/  MAX_ATTRIB_STACK_DEPTH ; 
 int /*<<< orphan*/  MAX_CLIENT_ATTRIB_STACK_DEPTH ; 
 int /*<<< orphan*/  MAX_CLIP_PLANES ; 
 int /*<<< orphan*/  MAX_EVAL_ORDER ; 
 int /*<<< orphan*/  MAX_HEIGHT ; 
 int /*<<< orphan*/  MAX_LIGHTS ; 
 int /*<<< orphan*/  MAX_LINE_WIDTH ; 
 int /*<<< orphan*/  MAX_LIST_NESTING ; 
 int /*<<< orphan*/  MAX_MODELVIEW_STACK_DEPTH ; 
 int /*<<< orphan*/  MAX_NAME_STACK_DEPTH ; 
 int /*<<< orphan*/  MAX_PIXEL_MAP_TABLE ; 
 int /*<<< orphan*/  MAX_POINT_SIZE ; 
 int /*<<< orphan*/  MAX_PROJECTION_STACK_DEPTH ; 
 int /*<<< orphan*/  MAX_TEXTURE_SIZE ; 
 int /*<<< orphan*/  MAX_TEXTURE_STACK_DEPTH ; 
 int /*<<< orphan*/  MAX_WIDTH ; 
 int /*<<< orphan*/  MIN_LINE_WIDTH ; 
 int /*<<< orphan*/  MIN_POINT_SIZE ; 
 int /*<<< orphan*/  NUM_AUX_BUFFERS ; 
 int /*<<< orphan*/  POINT_SIZE_GRANULARITY ; 
 int Q_BIT ; 
 int R_BIT ; 
 int S_BIT ; 
 int TEXTURE_1D ; 
 int TEXTURE_2D ; 
 int T_BIT ; 
 int /*<<< orphan*/  gl_error (TYPE_29__*,int /*<<< orphan*/ ,char*) ; 

void gl_GetIntegerv( GLcontext *ctx, GLenum pname, GLint *params )
{
   GLuint i;

   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glGetIntegerv" );
      return;
   }
   switch (pname) {
      case GL_ACCUM_RED_BITS:
      case GL_ACCUM_GREEN_BITS:
      case GL_ACCUM_BLUE_BITS:
      case GL_ACCUM_ALPHA_BITS:
         *params = (GLint) ctx->Visual->AccumBits;
         break;
      case GL_ACCUM_CLEAR_VALUE:
         params[0] = FLOAT_TO_INT( ctx->Accum.ClearColor[0] );
         params[1] = FLOAT_TO_INT( ctx->Accum.ClearColor[1] );
         params[2] = FLOAT_TO_INT( ctx->Accum.ClearColor[2] );
         params[3] = FLOAT_TO_INT( ctx->Accum.ClearColor[3] );
         break;
      case GL_ALPHA_BIAS:
         *params = (GLint) ctx->Pixel.AlphaBias;
         break;
      case GL_ALPHA_BITS:
         *params = ctx->Visual->AlphaBits;
         break;
      case GL_ALPHA_SCALE:
         *params = (GLint) ctx->Pixel.AlphaScale;
         break;
      case GL_ALPHA_TEST:
         *params = (GLint) ctx->Color.AlphaEnabled;
         break;
      case GL_ALPHA_TEST_REF:
         *params = FLOAT_TO_INT( ctx->Color.AlphaRef );
         break;
      case GL_ALPHA_TEST_FUNC:
         *params = (GLint) ctx->Color.AlphaFunc;
         break;
      case GL_ATTRIB_STACK_DEPTH:
         *params = (GLint) ctx->AttribStackDepth;
         break;
      case GL_AUTO_NORMAL:
         *params = (GLint) ctx->Eval.AutoNormal;
         break;
      case GL_AUX_BUFFERS:
         *params = (GLint) NUM_AUX_BUFFERS;
         break;
      case GL_BLEND:
         *params = (GLint) ctx->Color.BlendEnabled;
         break;
      case GL_BLEND_DST:
         *params = (GLint) ctx->Color.BlendDst;
         break;
      case GL_BLEND_SRC:
         *params = (GLint) ctx->Color.BlendSrc;
         break;
      case GL_BLUE_BIAS:
         *params = (GLint) ctx->Pixel.BlueBias;
         break;
      case GL_BLUE_BITS:
         *params = (GLint) ctx->Visual->BlueBits;
         break;
      case GL_BLUE_SCALE:
         *params = (GLint) ctx->Pixel.BlueScale;
         break;
      case GL_CLIENT_ATTRIB_STACK_DEPTH:
         *params = ctx->ClientAttribStackDepth;
         break;
      case GL_CLIP_PLANE0:
      case GL_CLIP_PLANE1:
      case GL_CLIP_PLANE2:
      case GL_CLIP_PLANE3:
      case GL_CLIP_PLANE4:
      case GL_CLIP_PLANE5:
         i = (GLint) (pname - GL_CLIP_PLANE0);
         *params = (GLint) ctx->Transform.ClipEnabled[i];
         break;
      case GL_COLOR_CLEAR_VALUE:
         params[0] = FLOAT_TO_INT( ctx->Color.ClearColor[0] );
         params[1] = FLOAT_TO_INT( ctx->Color.ClearColor[1] );
         params[2] = FLOAT_TO_INT( ctx->Color.ClearColor[2] );
         params[3] = FLOAT_TO_INT( ctx->Color.ClearColor[3] );
         break;
      case GL_COLOR_MATERIAL:
         *params = (GLint) ctx->Light.ColorMaterialEnabled;
         break;
      case GL_COLOR_MATERIAL_FACE:
         *params = (GLint) ctx->Light.ColorMaterialFace;
         break;
      case GL_COLOR_MATERIAL_PARAMETER:
         *params = (GLint) ctx->Light.ColorMaterialMode;
         break;
      case GL_COLOR_WRITEMASK:
         params[0] = (ctx->Color.ColorMask & 8) ? 1 : 0;
         params[1] = (ctx->Color.ColorMask & 4) ? 1 : 0;
         params[2] = (ctx->Color.ColorMask & 2) ? 1 : 0;
         params[3] = (ctx->Color.ColorMask & 1) ? 1 : 0;
         break;
      case GL_CULL_FACE:
         *params = (GLint) ctx->Polygon.CullFlag;
         break;
      case GL_CULL_FACE_MODE:
         *params = (GLint) ctx->Polygon.CullFaceMode;
         break;
      case GL_CURRENT_COLOR:
         params[0] = FLOAT_TO_INT( (ctx->Current.ByteColor[0]*ctx->Visual->InvRedScale) );
         params[1] = FLOAT_TO_INT( (ctx->Current.ByteColor[1]*ctx->Visual->InvGreenScale) );
         params[2] = FLOAT_TO_INT( (ctx->Current.ByteColor[2]*ctx->Visual->InvBlueScale) );
         params[3] = FLOAT_TO_INT( (ctx->Current.ByteColor[3]*ctx->Visual->InvAlphaScale) );
         break;
      case GL_CURRENT_INDEX:
         *params = (GLint) ctx->Current.Index;
         break;
      case GL_CURRENT_NORMAL:
         params[0] = FLOAT_TO_INT( ctx->Current.Normal[0] );
         params[1] = FLOAT_TO_INT( ctx->Current.Normal[1] );
         params[2] = FLOAT_TO_INT( ctx->Current.Normal[2] );
         break;
      case GL_CURRENT_RASTER_COLOR:
	 params[0] = FLOAT_TO_INT( ctx->Current.RasterColor[0] );
	 params[1] = FLOAT_TO_INT( ctx->Current.RasterColor[1] );
	 params[2] = FLOAT_TO_INT( ctx->Current.RasterColor[2] );
	 params[3] = FLOAT_TO_INT( ctx->Current.RasterColor[3] );
	 break;
      case GL_CURRENT_RASTER_DISTANCE:
	 params[0] = (GLint) ctx->Current.RasterDistance;
	 break;
      case GL_CURRENT_RASTER_INDEX:
	 *params = (GLint) ctx->Current.RasterIndex;
	 break;
      case GL_CURRENT_RASTER_POSITION:
	 params[0] = (GLint) ctx->Current.RasterPos[0];
	 params[1] = (GLint) ctx->Current.RasterPos[1];
	 params[2] = (GLint) ctx->Current.RasterPos[2];
	 params[3] = (GLint) ctx->Current.RasterPos[3];
	 break;
      case GL_CURRENT_RASTER_TEXTURE_COORDS:
	 params[0] = (GLint) ctx->Current.RasterTexCoord[0];
	 params[1] = (GLint) ctx->Current.RasterTexCoord[1];
	 params[2] = (GLint) ctx->Current.RasterTexCoord[2];
	 params[3] = (GLint) ctx->Current.RasterTexCoord[3];
	 break;
      case GL_CURRENT_RASTER_POSITION_VALID:
	 *params = (GLint) ctx->Current.RasterPosValid;
	 break;
      case GL_CURRENT_TEXTURE_COORDS:
         params[0] = (GLint) ctx->Current.TexCoord[0];
         params[1] = (GLint) ctx->Current.TexCoord[1];
         params[2] = (GLint) ctx->Current.TexCoord[2];
         params[3] = (GLint) ctx->Current.TexCoord[3];
	 break;
      case GL_DEPTH_BIAS:
         *params = (GLint) ctx->Pixel.DepthBias;
	 break;
      case GL_DEPTH_BITS:
	 *params = ctx->Visual->DepthBits;
	 break;
      case GL_DEPTH_CLEAR_VALUE:
         *params = (GLint) ctx->Depth.Clear;
	 break;
      case GL_DEPTH_FUNC:
         *params = (GLint) ctx->Depth.Func;
	 break;
      case GL_DEPTH_RANGE:
         params[0] = (GLint) ctx->Viewport.Near;
         params[1] = (GLint) ctx->Viewport.Far;
	 break;
      case GL_DEPTH_SCALE:
         *params = (GLint) ctx->Pixel.DepthScale;
	 break;
      case GL_DEPTH_TEST:
         *params = (GLint) ctx->Depth.Test;
	 break;
      case GL_DEPTH_WRITEMASK:
	 *params = (GLint) ctx->Depth.Mask;
	 break;
      case GL_DITHER:
	 *params = (GLint) ctx->Color.DitherFlag;
	 break;
      case GL_DOUBLEBUFFER:
	 *params = (GLint) ctx->Visual->DBflag;
	 break;
      case GL_DRAW_BUFFER:
	 *params = (GLint) ctx->Color.DrawBuffer;
	 break;
      case GL_EDGE_FLAG:
	 *params = (GLint) ctx->Current.EdgeFlag;
	 break;
      case GL_FEEDBACK_BUFFER_SIZE:
         /* TODO: is this right?  Or, return number of entries in buffer? */
         *params = ctx->Feedback.BufferSize;
         break;
      case GL_FEEDBACK_BUFFER_TYPE:
         *params = ctx->Feedback.Type;
         break;
      case GL_FOG:
	 *params = (GLint) ctx->Fog.Enabled;
	 break;
      case GL_FOG_COLOR:
	 params[0] = FLOAT_TO_INT( ctx->Fog.Color[0] );
	 params[1] = FLOAT_TO_INT( ctx->Fog.Color[1] );
	 params[2] = FLOAT_TO_INT( ctx->Fog.Color[2] );
	 params[3] = FLOAT_TO_INT( ctx->Fog.Color[3] );
	 break;
      case GL_FOG_DENSITY:
	 *params = (GLint) ctx->Fog.Density;
	 break;
      case GL_FOG_END:
	 *params = (GLint) ctx->Fog.End;
	 break;
      case GL_FOG_HINT:
	 *params = (GLint) ctx->Hint.Fog;
	 break;
      case GL_FOG_INDEX:
	 *params = (GLint) ctx->Fog.Index;
	 break;
      case GL_FOG_MODE:
	 *params = (GLint) ctx->Fog.Mode;
	 break;
      case GL_FOG_START:
	 *params = (GLint) ctx->Fog.Start;
	 break;
      case GL_FRONT_FACE:
	 *params = (GLint) ctx->Polygon.FrontFace;
	 break;
      case GL_GREEN_BIAS:
         *params = (GLint) ctx->Pixel.GreenBias;
         break;
      case GL_GREEN_BITS:
         *params = (GLint) ctx->Visual->GreenBits;
         break;
      case GL_GREEN_SCALE:
         *params = (GLint) ctx->Pixel.GreenScale;
         break;
      case GL_INDEX_BITS:
         *params = (GLint) ctx->Visual->IndexBits;
         break;
      case GL_INDEX_CLEAR_VALUE:
         *params = (GLint) ctx->Color.ClearIndex;
         break;
      case GL_INDEX_MODE:
	 *params = ctx->Visual->RGBAflag ? 0 : 1;
	 break;
      case GL_INDEX_OFFSET:
	 *params = ctx->Pixel.IndexOffset;
	 break;
      case GL_INDEX_SHIFT:
	 *params = ctx->Pixel.IndexShift;
	 break;
      case GL_INDEX_WRITEMASK:
	 *params = (GLint) ctx->Color.IndexMask;
	 break;
      case GL_LIGHT0:
      case GL_LIGHT1:
      case GL_LIGHT2:
      case GL_LIGHT3:
      case GL_LIGHT4:
      case GL_LIGHT5:
      case GL_LIGHT6:
      case GL_LIGHT7:
	 *params = (GLint) ctx->Light.Light[pname-GL_LIGHT0].Enabled;
	 break;
      case GL_LIGHTING:
	 *params = (GLint) ctx->Light.Enabled;
	 break;
      case GL_LIGHT_MODEL_AMBIENT:
	 params[0] = FLOAT_TO_INT( ctx->Light.Model.Ambient[0] );
	 params[1] = FLOAT_TO_INT( ctx->Light.Model.Ambient[1] );
	 params[2] = FLOAT_TO_INT( ctx->Light.Model.Ambient[2] );
	 params[3] = FLOAT_TO_INT( ctx->Light.Model.Ambient[3] );
	 break;
      case GL_LIGHT_MODEL_LOCAL_VIEWER:
	 *params = (GLint) ctx->Light.Model.LocalViewer;
	 break;
      case GL_LIGHT_MODEL_TWO_SIDE:
	 *params = (GLint) ctx->Light.Model.TwoSide;
	 break;
      case GL_LINE_SMOOTH:
	 *params = (GLint) ctx->Line.SmoothFlag;
	 break;
      case GL_LINE_SMOOTH_HINT:
	 *params = (GLint) ctx->Hint.LineSmooth;
	 break;
      case GL_LINE_STIPPLE:
	 *params = (GLint) ctx->Line.StippleFlag;
	 break;
      case GL_LINE_STIPPLE_PATTERN:
         *params = (GLint) ctx->Line.StipplePattern;
         break;
      case GL_LINE_STIPPLE_REPEAT:
         *params = (GLint) ctx->Line.StippleFactor;
         break;
      case GL_LINE_WIDTH:
	 *params = (GLint) ctx->Line.Width;
	 break;
      case GL_LINE_WIDTH_GRANULARITY:
	 *params = (GLint) LINE_WIDTH_GRANULARITY;
	 break;
      case GL_LINE_WIDTH_RANGE:
	 params[0] = (GLint) MIN_LINE_WIDTH;
	 params[1] = (GLint) MAX_LINE_WIDTH;
	 break;
      case GL_LIST_BASE:
	 *params = (GLint) ctx->List.ListBase;
	 break;
      case GL_LIST_INDEX:
	 *params = (GLint) ctx->CurrentListNum;
	 break;
      case GL_LIST_MODE:
	 *params = ctx->ExecuteFlag ? (GLint) GL_COMPILE_AND_EXECUTE
	   			  : (GLint) GL_COMPILE;
	 break;
      case GL_INDEX_LOGIC_OP:
	 *params = (GLint) ctx->Color.IndexLogicOpEnabled;
	 break;
      case GL_COLOR_LOGIC_OP:
	 *params = (GLint) ctx->Color.ColorLogicOpEnabled;
	 break;
      case GL_LOGIC_OP_MODE:
         *params = (GLint) ctx->Color.LogicOp;
         break;
      case GL_MAP1_COLOR_4:
	 *params = (GLint) ctx->Eval.Map1Color4;
	 break;
      case GL_MAP1_GRID_DOMAIN:
	 params[0] = (GLint) ctx->Eval.MapGrid1u1;
	 params[1] = (GLint) ctx->Eval.MapGrid1u2;
	 break;
      case GL_MAP1_GRID_SEGMENTS:
	 *params = (GLint) ctx->Eval.MapGrid1un;
	 break;
      case GL_MAP1_INDEX:
	 *params = (GLint) ctx->Eval.Map1Index;
	 break;
      case GL_MAP1_NORMAL:
	 *params = (GLint) ctx->Eval.Map1Normal;
	 break;
      case GL_MAP1_TEXTURE_COORD_1:
	 *params = (GLint) ctx->Eval.Map1TextureCoord1;
	 break;
      case GL_MAP1_TEXTURE_COORD_2:
	 *params = (GLint) ctx->Eval.Map1TextureCoord2;
	 break;
      case GL_MAP1_TEXTURE_COORD_3:
	 *params = (GLint) ctx->Eval.Map1TextureCoord3;
	 break;
      case GL_MAP1_TEXTURE_COORD_4:
	 *params = (GLint) ctx->Eval.Map1TextureCoord4;
	 break;
      case GL_MAP1_VERTEX_3:
	 *params = (GLint) ctx->Eval.Map1Vertex3;
	 break;
      case GL_MAP1_VERTEX_4:
	 *params = (GLint) ctx->Eval.Map1Vertex4;
	 break;
      case GL_MAP2_COLOR_4:
	 *params = (GLint) ctx->Eval.Map2Color4;
	 break;
      case GL_MAP2_GRID_DOMAIN:
	 params[0] = (GLint) ctx->Eval.MapGrid2u1;
	 params[1] = (GLint) ctx->Eval.MapGrid2u2;
	 params[2] = (GLint) ctx->Eval.MapGrid2v1;
	 params[3] = (GLint) ctx->Eval.MapGrid2v2;
	 break;
      case GL_MAP2_GRID_SEGMENTS:
	 params[0] = (GLint) ctx->Eval.MapGrid2un;
	 params[1] = (GLint) ctx->Eval.MapGrid2vn;
	 break;
      case GL_MAP2_INDEX:
	 *params = (GLint) ctx->Eval.Map2Index;
	 break;
      case GL_MAP2_NORMAL:
	 *params = (GLint) ctx->Eval.Map2Normal;
	 break;
      case GL_MAP2_TEXTURE_COORD_1:
	 *params = (GLint) ctx->Eval.Map2TextureCoord1;
	 break;
      case GL_MAP2_TEXTURE_COORD_2:
	 *params = (GLint) ctx->Eval.Map2TextureCoord2;
	 break;
      case GL_MAP2_TEXTURE_COORD_3:
	 *params = (GLint) ctx->Eval.Map2TextureCoord3;
	 break;
      case GL_MAP2_TEXTURE_COORD_4:
	 *params = (GLint) ctx->Eval.Map2TextureCoord4;
	 break;
      case GL_MAP2_VERTEX_3:
	 *params = (GLint) ctx->Eval.Map2Vertex3;
	 break;
      case GL_MAP2_VERTEX_4:
	 *params = (GLint) ctx->Eval.Map2Vertex4;
	 break;
      case GL_MAP_COLOR:
	 *params = (GLint) ctx->Pixel.MapColorFlag;
	 break;
      case GL_MAP_STENCIL:
	 *params = (GLint) ctx->Pixel.MapStencilFlag;
	 break;
      case GL_MATRIX_MODE:
	 *params = (GLint) ctx->Transform.MatrixMode;
	 break;
      case GL_MAX_ATTRIB_STACK_DEPTH:
         *params = (GLint) MAX_ATTRIB_STACK_DEPTH;
         break;
      case GL_MAX_CLIENT_ATTRIB_STACK_DEPTH:
         *params = (GLint) MAX_CLIENT_ATTRIB_STACK_DEPTH;
         break;
      case GL_MAX_CLIP_PLANES:
         *params = (GLint) MAX_CLIP_PLANES;
         break;
      case GL_MAX_EVAL_ORDER:
	 *params = (GLint) MAX_EVAL_ORDER;
	 break;
      case GL_MAX_LIGHTS:
         *params = (GLint) MAX_LIGHTS;
         break;
      case GL_MAX_LIST_NESTING:
         *params = (GLint) MAX_LIST_NESTING;
         break;
      case GL_MAX_MODELVIEW_STACK_DEPTH:
         *params = (GLint) MAX_MODELVIEW_STACK_DEPTH;
         break;
      case GL_MAX_NAME_STACK_DEPTH:
	 *params = (GLint) MAX_NAME_STACK_DEPTH;
	 break;
      case GL_MAX_PIXEL_MAP_TABLE:
	 *params = (GLint) MAX_PIXEL_MAP_TABLE;
	 break;
      case GL_MAX_PROJECTION_STACK_DEPTH:
         *params = (GLint) MAX_PROJECTION_STACK_DEPTH;
         break;
      case GL_MAX_TEXTURE_SIZE:
	 *params = (GLint) MAX_TEXTURE_SIZE;
	 break;
      case GL_MAX_TEXTURE_STACK_DEPTH:
	 *params = (GLint) MAX_TEXTURE_STACK_DEPTH;
	 break;
      case GL_MAX_VIEWPORT_DIMS:
         params[0] = (GLint) MAX_WIDTH;
         params[1] = (GLint) MAX_HEIGHT;
         break;
      case GL_MODELVIEW_MATRIX:
	 for (i=0;i<16;i++) {
	    params[i] = (GLint) ctx->ModelViewMatrix[i];
	 }
	 break;
      case GL_MODELVIEW_STACK_DEPTH:
	 *params = (GLint) ctx->ModelViewStackDepth;
	 break;
      case GL_NAME_STACK_DEPTH:
	 *params = (GLint) ctx->Select.NameStackDepth;
	 break;
      case GL_NORMALIZE:
	 *params = (GLint) ctx->Transform.Normalize;
	 break;
      case GL_PACK_ALIGNMENT:
	 *params = ctx->Pack.Alignment;
	 break;
      case GL_PACK_LSB_FIRST:
	 *params = (GLint) ctx->Pack.LsbFirst;
	 break;
      case GL_PACK_ROW_LENGTH:
	 *params = ctx->Pack.RowLength;
	 break;
      case GL_PACK_SKIP_PIXELS:
	 *params = ctx->Pack.SkipPixels;
	 break;
      case GL_PACK_SKIP_ROWS:
	 *params = ctx->Pack.SkipRows;
	 break;
      case GL_PACK_SWAP_BYTES:
	 *params = (GLint) ctx->Pack.SwapBytes;
	 break;
      case GL_PERSPECTIVE_CORRECTION_HINT:
	 *params = (GLint) ctx->Hint.PerspectiveCorrection;
	 break;
      case GL_PIXEL_MAP_A_TO_A_SIZE:
	 *params = ctx->Pixel.MapAtoAsize;
	 break;
      case GL_PIXEL_MAP_B_TO_B_SIZE:
	 *params = ctx->Pixel.MapBtoBsize;
	 break;
      case GL_PIXEL_MAP_G_TO_G_SIZE:
	 *params = ctx->Pixel.MapGtoGsize;
	 break;
      case GL_PIXEL_MAP_I_TO_A_SIZE:
	 *params = ctx->Pixel.MapItoAsize;
	 break;
      case GL_PIXEL_MAP_I_TO_B_SIZE:
	 *params = ctx->Pixel.MapItoBsize;
	 break;
      case GL_PIXEL_MAP_I_TO_G_SIZE:
	 *params = ctx->Pixel.MapItoGsize;
	 break;
      case GL_PIXEL_MAP_I_TO_I_SIZE:
	 *params = ctx->Pixel.MapItoIsize;
	 break;
      case GL_PIXEL_MAP_I_TO_R_SIZE:
	 *params = ctx->Pixel.MapItoRsize;
	 break;
      case GL_PIXEL_MAP_R_TO_R_SIZE:
	 *params = ctx->Pixel.MapRtoRsize;
	 break;
      case GL_PIXEL_MAP_S_TO_S_SIZE:
	 *params = ctx->Pixel.MapStoSsize;
	 break;
      case GL_POINT_SIZE:
         *params = (GLint) ctx->Point.Size;
         break;
      case GL_POINT_SIZE_GRANULARITY:
	 *params = (GLint) POINT_SIZE_GRANULARITY;
	 break;
      case GL_POINT_SIZE_RANGE:
	 params[0] = (GLint) MIN_POINT_SIZE;
	 params[1] = (GLint) MAX_POINT_SIZE;
	 break;
      case GL_POINT_SMOOTH:
	 *params = (GLint) ctx->Point.SmoothFlag;
	 break;
      case GL_POINT_SMOOTH_HINT:
	 *params = (GLint) ctx->Hint.PointSmooth;
	 break;
      case GL_POLYGON_MODE:
	 params[0] = (GLint) ctx->Polygon.FrontMode;
	 params[1] = (GLint) ctx->Polygon.BackMode;
	 break;
#ifdef GL_EXT_polygon_offset
      case GL_POLYGON_OFFSET_BIAS_EXT:
         *params = (GLint) ctx->Polygon.OffsetUnits;
         break;
#endif
      case GL_POLYGON_OFFSET_FACTOR:
         *params = (GLint) ctx->Polygon.OffsetFactor;
         break;
      case GL_POLYGON_OFFSET_UNITS:
         *params = (GLint) ctx->Polygon.OffsetUnits;
         break;
      case GL_POLYGON_SMOOTH:
	 *params = (GLint) ctx->Polygon.SmoothFlag;
	 break;
      case GL_POLYGON_SMOOTH_HINT:
	 *params = (GLint) ctx->Hint.PolygonSmooth;
	 break;
      case GL_POLYGON_STIPPLE:
	 for (i=0;i<32;i++) {		/* RIGHT? */
	    params[i] = (GLint) ctx->PolygonStipple[i];
	 }
	 break;
      case GL_PROJECTION_MATRIX:
	 for (i=0;i<16;i++) {
	    params[i] = (GLint) ctx->ProjectionMatrix[i];
	 }
	 break;
      case GL_PROJECTION_STACK_DEPTH:
	 *params = (GLint) ctx->ProjectionStackDepth;
	 break;
      case GL_READ_BUFFER:
	 *params = (GLint) ctx->Pixel.ReadBuffer;
	 break;
      case GL_RED_BIAS:
         *params = (GLint) ctx->Pixel.RedBias;
         break;
      case GL_RED_BITS:
         *params = (GLint) ctx->Visual->RedBits;
         break;
      case GL_RED_SCALE:
         *params = (GLint) ctx->Pixel.RedScale;
         break;
      case GL_RENDER_MODE:
	 *params = (GLint) ctx->RenderMode;
	 break;
      case GL_RGBA_MODE:
	 *params = (GLint) ctx->Visual->RGBAflag;
	 break;
      case GL_SCISSOR_BOX:
	 params[0] = (GLint) ctx->Scissor.X;
	 params[1] = (GLint) ctx->Scissor.Y;
	 params[2] = (GLint) ctx->Scissor.Width;
	 params[3] = (GLint) ctx->Scissor.Height;
	 break;
      case GL_SCISSOR_TEST:
	 *params = (GLint) ctx->Scissor.Enabled;
	 break;
      case GL_SHADE_MODEL:
	 *params = (GLint) ctx->Light.ShadeModel;
	 break;
      case GL_STENCIL_BITS:
         *params = ctx->Visual->StencilBits;
         break;
      case GL_STENCIL_CLEAR_VALUE:
	 *params = (GLint) ctx->Stencil.Clear;
	 break;
      case GL_STENCIL_FAIL:
	 *params = (GLint) ctx->Stencil.FailFunc;
	 break;
      case GL_STENCIL_FUNC:
	 *params = (GLint) ctx->Stencil.Function;
	 break;
      case GL_STENCIL_PASS_DEPTH_FAIL:
	 *params = (GLint) ctx->Stencil.ZFailFunc;
	 break;
      case GL_STENCIL_PASS_DEPTH_PASS:
	 *params = (GLint) ctx->Stencil.ZPassFunc;
	 break;
      case GL_STENCIL_REF:
	 *params = (GLint) ctx->Stencil.Ref;
	 break;
      case GL_STENCIL_TEST:
	 *params = (GLint) ctx->Stencil.Enabled;
	 break;
      case GL_STENCIL_VALUE_MASK:
	 *params = (GLint) ctx->Stencil.ValueMask;
	 break;
      case GL_STENCIL_WRITEMASK:
	 *params = (GLint) ctx->Stencil.WriteMask;
	 break;
      case GL_STEREO:
	 *params = 0;  /* TODO */
	 break;
      case GL_SUBPIXEL_BITS:
	 *params = 0;  /* TODO */
	 break;
      case GL_TEXTURE_1D:
	 *params = (ctx->Texture.Enabled & TEXTURE_1D) ? 1.0 : 0.0;
	 break;
      case GL_TEXTURE_2D:
	 *params = (ctx->Texture.Enabled & TEXTURE_2D) ? 1.0 : 0.0;
	 break;
      case GL_TEXTURE_ENV_COLOR:
	 params[0] = FLOAT_TO_INT( ctx->Texture.EnvColor[0] );
	 params[1] = FLOAT_TO_INT( ctx->Texture.EnvColor[1] );
	 params[2] = FLOAT_TO_INT( ctx->Texture.EnvColor[2] );
	 params[3] = FLOAT_TO_INT( ctx->Texture.EnvColor[3] );
	 break;
      case GL_TEXTURE_ENV_MODE:
	 *params = (GLint) ctx->Texture.EnvMode;
	 break;
      case GL_TEXTURE_GEN_S:
	 *params = (ctx->Texture.TexGenEnabled & S_BIT) ? 1 : 0;
	 break;
      case GL_TEXTURE_GEN_T:
	 *params = (ctx->Texture.TexGenEnabled & T_BIT) ? 1 : 0;
	 break;
      case GL_TEXTURE_GEN_R:
	 *params = (ctx->Texture.TexGenEnabled & R_BIT) ? 1 : 0;
	 break;
      case GL_TEXTURE_GEN_Q:
	 *params = (ctx->Texture.TexGenEnabled & Q_BIT) ? 1 : 0;
	 break;
      case GL_TEXTURE_MATRIX:
         for (i=0;i<16;i++) {
	    params[i] = (GLint) ctx->TextureMatrix[i];
	 }
	 break;
      case GL_TEXTURE_STACK_DEPTH:
	 *params = (GLint) ctx->TextureStackDepth;
	 break;
      case GL_UNPACK_ALIGNMENT:
	 *params = ctx->Unpack.Alignment;
	 break;
      case GL_UNPACK_LSB_FIRST:
	 *params = (GLint) ctx->Unpack.LsbFirst;
	 break;
      case GL_UNPACK_ROW_LENGTH:
	 *params = ctx->Unpack.RowLength;
	 break;
      case GL_UNPACK_SKIP_PIXELS:
	 *params = ctx->Unpack.SkipPixels;
	 break;
      case GL_UNPACK_SKIP_ROWS:
	 *params = ctx->Unpack.SkipRows;
	 break;
      case GL_UNPACK_SWAP_BYTES:
	 *params = (GLint) ctx->Unpack.SwapBytes;
	 break;
      case GL_VIEWPORT:
         params[0] = (GLint) ctx->Viewport.X;
         params[1] = (GLint) ctx->Viewport.Y;
         params[2] = (GLint) ctx->Viewport.Width;
         params[3] = (GLint) ctx->Viewport.Height;
         break;
      case GL_ZOOM_X:
	 *params = (GLint) ctx->Pixel.ZoomX;
	 break;
      case GL_ZOOM_Y:
	 *params = (GLint) ctx->Pixel.ZoomY;
	 break;
      case GL_VERTEX_ARRAY_SIZE:
         *params = ctx->Array.VertexSize;
         break;
      case GL_VERTEX_ARRAY_TYPE:
         *params = ctx->Array.VertexType;
         break;
      case GL_VERTEX_ARRAY_STRIDE:
         *params = ctx->Array.VertexStride;
         break;
      case GL_VERTEX_ARRAY_COUNT_EXT:
         *params = 0;
         break;
      case GL_NORMAL_ARRAY_TYPE:
         *params = ctx->Array.NormalType;
         break;
      case GL_NORMAL_ARRAY_STRIDE:
         *params = ctx->Array.NormalStride;
         break;
      case GL_NORMAL_ARRAY_COUNT_EXT:
         *params = 0;
         break;
      case GL_COLOR_ARRAY_SIZE:
         *params = ctx->Array.ColorSize;
         break;
      case GL_COLOR_ARRAY_TYPE:
         *params = ctx->Array.ColorType;
         break;
      case GL_COLOR_ARRAY_STRIDE:
         *params = ctx->Array.ColorStride;
         break;
      case GL_COLOR_ARRAY_COUNT_EXT:
         *params = 0;
         break;
      case GL_INDEX_ARRAY_TYPE:
         *params = ctx->Array.IndexType;
         break;
      case GL_INDEX_ARRAY_STRIDE:
         *params = ctx->Array.IndexStride;
         break;
      case GL_INDEX_ARRAY_COUNT_EXT:
         *params = 0;
         break;
      case GL_TEXTURE_COORD_ARRAY_SIZE:
         *params = ctx->Array.TexCoordSize;
         break;
      case GL_TEXTURE_COORD_ARRAY_TYPE:
         *params = ctx->Array.TexCoordType;
         break;
      case GL_TEXTURE_COORD_ARRAY_STRIDE:
         *params = ctx->Array.TexCoordStride;
         break;
      case GL_TEXTURE_COORD_ARRAY_COUNT_EXT:
         *params = 0;
         break;
      case GL_EDGE_FLAG_ARRAY_STRIDE:
         *params = ctx->Array.EdgeFlagStride;
         break;
      case GL_EDGE_FLAG_ARRAY_COUNT_EXT:
         *params = 0;
         break;
      case GL_TEXTURE_BINDING_1D:
         *params = ctx->Texture.Current1D->Name;
          break;
      case GL_TEXTURE_BINDING_2D:
         *params = ctx->Texture.Current2D->Name;
          break;

      default:
         gl_error( ctx, GL_INVALID_ENUM, "glGetIntegerv" );
   }
}