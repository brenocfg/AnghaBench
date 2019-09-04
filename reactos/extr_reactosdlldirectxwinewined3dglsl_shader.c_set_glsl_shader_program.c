#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct wined3d_string_buffer {int /*<<< orphan*/  buffer; } ;
struct wined3d_state {scalar_t__ gl_primitive_type; scalar_t__* render_states; struct wined3d_shader** shader; } ;
struct TYPE_23__ {int major; } ;
struct TYPE_26__ {int input_registers; scalar_t__ boolean_constants; scalar_t__ integer_constants; TYPE_6__ shader_version; int /*<<< orphan*/  clip_distance_mask; scalar_t__ point_size; } ;
struct TYPE_24__ {scalar_t__ declared_in_count; } ;
struct TYPE_25__ {TYPE_7__ ps; } ;
struct list {int dummy; } ;
struct wined3d_shader {TYPE_9__ reg_maps; TYPE_8__ u; TYPE_5__* limits; struct list linked_programs; } ;
struct TYPE_20__ {int dual_buffers; unsigned int buffers; } ;
struct wined3d_gl_info {TYPE_3__ limits; } ;
struct wined3d_ffp_vs_settings {int dummy; } ;
struct wined3d_d3d_info {scalar_t__ emulated_flatshading; } ;
struct TYPE_18__ {int /*<<< orphan*/  position_transformed; int /*<<< orphan*/  swizzle_map; } ;
struct wined3d_context {unsigned int shader_update_mask; TYPE_1__ stream_info; struct wined3d_gl_info* gl_info; struct wined3d_d3d_info* d3d_info; } ;
struct vs_compile_args {int dummy; } ;
struct shader_glsl_priv {int /*<<< orphan*/  string_buffers; int /*<<< orphan*/ * fragment_pipe; int /*<<< orphan*/  shader_buffer; int /*<<< orphan*/ * vertex_pipe; } ;
struct ps_np2fixup_info {int dummy; } ;
struct ps_compile_args {int dummy; } ;
struct gs_compile_args {int dummy; } ;
struct TYPE_15__ {int ycorrection_location; int* bumpenv_mat_location; int fog_color_location; int alpha_test_ref_location; int np2_fixup_location; int color_key_location; struct list shader_entry; struct ps_np2fixup_info const* np2_fixup_info; void* id; } ;
struct TYPE_16__ {int pos_fixup_location; struct list shader_entry; void* id; } ;
struct TYPE_17__ {int pos_fixup_location; struct list shader_entry; void* id; } ;
struct TYPE_14__ {int pos_fixup_location; int* modelview_matrix_location; int* texture_matrix_location; int material_ambient_location; int material_diffuse_location; int material_specular_location; int material_emissive_location; int material_shininess_location; int light_ambient_location; int clip_planes_location; int pointsize_min_location; void* vertex_color_clamp; struct list shader_entry; void* id; } ;
struct TYPE_21__ {struct list shader_entry; void* id; } ;
struct TYPE_19__ {scalar_t__ id; } ;
struct glsl_shader_prog_link {int shader_controlled_clip_distances; unsigned int clip_distance_mask; int constant_update_mask; TYPE_11__ ps; TYPE_12__ gs; TYPE_13__ ds; TYPE_10__ vs; TYPE_4__ hs; scalar_t__ constant_version; TYPE_2__ cs; void* id; } ;
struct glsl_program_key {scalar_t__ cs_id; void* ps_id; void* gs_id; void* ds_id; void* hs_id; void* vs_id; } ;
struct glsl_ffp_vertex_shader {struct list linked_programs; void* id; } ;
struct glsl_ffp_fragment_shader {struct list linked_programs; void* id; } ;
struct glsl_context_data {struct glsl_shader_prog_link* glsl_program; } ;
struct ffp_frag_settings {int dummy; } ;
struct ds_compile_args {int dummy; } ;
typedef  int WORD ;
struct TYPE_22__ {int /*<<< orphan*/  constant_float; } ;
typedef  void* GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 void* GL_EXTCALL (int /*<<< orphan*/ ) ; 
 void* GL_FALSE ; 
 void* GL_FIXED_ONLY_ARB ; 
 scalar_t__ GL_POINTS ; 
 unsigned int MAX_TEXTURES ; 
 unsigned int MAX_VERTEX_INDEX_BLENDS ; 
 int /*<<< orphan*/  TRACE (char*,void*,...) ; 
 unsigned int WINED3D_FFP_ATTRIBS_COUNT ; 
 size_t WINED3D_RS_SHADEMODE ; 
 int WINED3D_SHADER_CONST_FFP_COLOR_KEY ; 
 int WINED3D_SHADER_CONST_FFP_LIGHTS ; 
 int WINED3D_SHADER_CONST_FFP_MATERIAL ; 
 int WINED3D_SHADER_CONST_FFP_MODELVIEW ; 
 int WINED3D_SHADER_CONST_FFP_PROJ ; 
 int WINED3D_SHADER_CONST_FFP_PS ; 
 int WINED3D_SHADER_CONST_FFP_TEXMATRIX ; 
 int WINED3D_SHADER_CONST_FFP_VERTEXBLEND ; 
 int WINED3D_SHADER_CONST_POS_FIXUP ; 
 int WINED3D_SHADER_CONST_PS_ALPHA_TEST ; 
 int WINED3D_SHADER_CONST_PS_B ; 
 int WINED3D_SHADER_CONST_PS_BUMP_ENV ; 
 int WINED3D_SHADER_CONST_PS_F ; 
 int WINED3D_SHADER_CONST_PS_FOG ; 
 int WINED3D_SHADER_CONST_PS_I ; 
 int WINED3D_SHADER_CONST_PS_NP2_FIXUP ; 
 int WINED3D_SHADER_CONST_PS_Y_CORR ; 
 int WINED3D_SHADER_CONST_VS_B ; 
 int WINED3D_SHADER_CONST_VS_CLIP_PLANES ; 
 int WINED3D_SHADER_CONST_VS_F ; 
 int WINED3D_SHADER_CONST_VS_I ; 
 int WINED3D_SHADER_CONST_VS_POINTSIZE ; 
 size_t WINED3D_SHADER_TYPE_DOMAIN ; 
 size_t WINED3D_SHADER_TYPE_GEOMETRY ; 
 size_t WINED3D_SHADER_TYPE_HULL ; 
 unsigned int WINED3D_SHADER_TYPE_PIXEL ; 
 unsigned int WINED3D_SHADER_TYPE_VERTEX ; 
 scalar_t__ WINED3D_SHADE_FLAT ; 
 int /*<<< orphan*/  add_glsl_program_entry (struct shader_glsl_priv*,struct glsl_shader_prog_link*) ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  find_ds_compile_args (struct wined3d_state const*,struct wined3d_shader*,struct ds_compile_args*,struct wined3d_context const*) ; 
 void* find_glsl_domain_shader (struct wined3d_context const*,struct shader_glsl_priv*,struct wined3d_shader*,struct ds_compile_args*) ; 
 void* find_glsl_geometry_shader (struct wined3d_context const*,struct shader_glsl_priv*,struct wined3d_shader*,struct gs_compile_args*) ; 
 void* find_glsl_hull_shader (struct wined3d_context const*,struct shader_glsl_priv*,struct wined3d_shader*) ; 
 void* find_glsl_pshader (struct wined3d_context const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct wined3d_shader*,struct ps_compile_args*,struct ps_np2fixup_info const**) ; 
 void* find_glsl_vshader (struct wined3d_context const*,struct shader_glsl_priv*,struct wined3d_shader*,struct vs_compile_args*) ; 
 int /*<<< orphan*/  find_gs_compile_args (struct wined3d_state const*,struct wined3d_shader*,struct gs_compile_args*,struct wined3d_context const*) ; 
 int /*<<< orphan*/  find_ps_compile_args (struct wined3d_state const*,struct wined3d_shader*,int /*<<< orphan*/ ,struct ps_compile_args*,struct wined3d_context const*) ; 
 int /*<<< orphan*/  find_vs_compile_args (struct wined3d_state const*,struct wined3d_shader*,int /*<<< orphan*/ ,struct vs_compile_args*,struct wined3d_context const*) ; 
 int /*<<< orphan*/  gen_ffp_frag_op (struct wined3d_context const*,struct wined3d_state const*,struct ffp_frag_settings*,int /*<<< orphan*/ ) ; 
 struct glsl_shader_prog_link* get_glsl_program_entry (struct shader_glsl_priv*,struct glsl_program_key*) ; 
 int /*<<< orphan*/  glAttachShader (void*,void*) ; 
 int /*<<< orphan*/  glBindAttribLocation (void*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindFragDataLocation (void*,unsigned int,char*) ; 
 int /*<<< orphan*/  glBindFragDataLocationIndexed (void*,unsigned int,unsigned int,char*) ; 
 int /*<<< orphan*/  glCreateProgram () ; 
 int /*<<< orphan*/  glDeleteShader (void*) ; 
 int /*<<< orphan*/  glLinkProgram (void*) ; 
 int /*<<< orphan*/  glUseProgram (void*) ; 
 int /*<<< orphan*/  glsl_fragment_pipe ; 
 int /*<<< orphan*/  glsl_vertex_pipe ; 
 struct glsl_shader_prog_link* heap_alloc (int) ; 
 scalar_t__ is_rasterization_disabled (struct wined3d_shader*) ; 
 int /*<<< orphan*/  list_add_head (struct list*,struct list*) ; 
 scalar_t__ needs_legacy_glsl_syntax (struct wined3d_gl_info const*) ; 
 struct glsl_ffp_fragment_shader* shader_glsl_find_ffp_fragment_shader (struct shader_glsl_priv*,struct ffp_frag_settings*,struct wined3d_context const*) ; 
 struct glsl_ffp_vertex_shader* shader_glsl_find_ffp_vertex_shader (struct shader_glsl_priv*,struct wined3d_gl_info const*,struct wined3d_ffp_vs_settings*) ; 
 void* shader_glsl_generate_vs3_rasterizer_input_setup (struct shader_glsl_priv*,struct wined3d_shader*,struct wined3d_shader*,int,int,struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_glsl_init_ds_uniform_locations (struct wined3d_gl_info const*,struct shader_glsl_priv*,void*,TYPE_13__*) ; 
 int /*<<< orphan*/  shader_glsl_init_gs_uniform_locations (struct wined3d_gl_info const*,struct shader_glsl_priv*,void*,TYPE_12__*) ; 
 int /*<<< orphan*/  shader_glsl_init_ps_uniform_locations (struct wined3d_gl_info const*,struct shader_glsl_priv*,void*,TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_init_transform_feedback (struct wined3d_context const*,struct shader_glsl_priv*,void*,struct wined3d_shader*) ; 
 int /*<<< orphan*/  shader_glsl_init_vs_uniform_locations (struct wined3d_gl_info const*,struct shader_glsl_priv*,void*,TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_load_images (struct wined3d_gl_info const*,struct shader_glsl_priv*,void*,TYPE_9__*) ; 
 int /*<<< orphan*/  shader_glsl_load_program_resources (struct wined3d_context const*,struct shader_glsl_priv*,void*,struct wined3d_shader*) ; 
 int /*<<< orphan*/  shader_glsl_load_samplers (struct wined3d_context const*,struct shader_glsl_priv*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shader_glsl_use_explicit_attrib_location (struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_glsl_validate_link (struct wined3d_gl_info const*,void*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 struct wined3d_string_buffer* string_buffer_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_buffer_release (int /*<<< orphan*/ *,struct wined3d_string_buffer*) ; 
 int /*<<< orphan*/  string_buffer_sprintf (struct wined3d_string_buffer*,char*,unsigned int) ; 
 scalar_t__ use_ps (struct wined3d_state const*) ; 
 scalar_t__ use_vs (struct wined3d_state const*) ; 
 scalar_t__ vec4_varyings (int,struct wined3d_gl_info const*) ; 
 scalar_t__ wined3d_dualblend_enabled (struct wined3d_state const*,struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  wined3d_ffp_get_vs_settings (struct wined3d_context const*,struct wined3d_state const*,struct wined3d_ffp_vs_settings*) ; 
 unsigned int wined3d_popcount (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_glsl_shader_program(const struct wined3d_context *context, const struct wined3d_state *state,
        struct shader_glsl_priv *priv, struct glsl_context_data *ctx_data)
{
    const struct wined3d_d3d_info *d3d_info = context->d3d_info;
    const struct wined3d_gl_info *gl_info = context->gl_info;
    const struct wined3d_shader *pre_rasterization_shader;
    const struct ps_np2fixup_info *np2fixup_info = NULL;
    struct wined3d_shader *hshader, *dshader, *gshader;
    struct glsl_shader_prog_link *entry = NULL;
    struct wined3d_shader *vshader = NULL;
    struct wined3d_shader *pshader = NULL;
    GLuint reorder_shader_id = 0;
    struct glsl_program_key key;
    GLuint program_id;
    unsigned int i;
    GLuint vs_id = 0;
    GLuint hs_id = 0;
    GLuint ds_id = 0;
    GLuint gs_id = 0;
    GLuint ps_id = 0;
    struct list *ps_list = NULL, *vs_list = NULL;
    WORD attribs_map;
    struct wined3d_string_buffer *tmp_name;

    if (!(context->shader_update_mask & (1u << WINED3D_SHADER_TYPE_VERTEX)) && ctx_data->glsl_program)
    {
        vs_id = ctx_data->glsl_program->vs.id;
        vs_list = &ctx_data->glsl_program->vs.shader_entry;

        if (use_vs(state))
            vshader = state->shader[WINED3D_SHADER_TYPE_VERTEX];
    }
    else if (use_vs(state))
    {
        struct vs_compile_args vs_compile_args;

        vshader = state->shader[WINED3D_SHADER_TYPE_VERTEX];

        find_vs_compile_args(state, vshader, context->stream_info.swizzle_map, &vs_compile_args, context);
        vs_id = find_glsl_vshader(context, priv, vshader, &vs_compile_args);
        vs_list = &vshader->linked_programs;
    }
    else if (priv->vertex_pipe == &glsl_vertex_pipe)
    {
        struct glsl_ffp_vertex_shader *ffp_shader;
        struct wined3d_ffp_vs_settings settings;

        wined3d_ffp_get_vs_settings(context, state, &settings);
        ffp_shader = shader_glsl_find_ffp_vertex_shader(priv, gl_info, &settings);
        vs_id = ffp_shader->id;
        vs_list = &ffp_shader->linked_programs;
    }

    hshader = state->shader[WINED3D_SHADER_TYPE_HULL];
    if (!(context->shader_update_mask & (1u << WINED3D_SHADER_TYPE_HULL)) && ctx_data->glsl_program)
        hs_id = ctx_data->glsl_program->hs.id;
    else if (hshader)
        hs_id = find_glsl_hull_shader(context, priv, hshader);

    dshader = state->shader[WINED3D_SHADER_TYPE_DOMAIN];
    if (!(context->shader_update_mask & (1u << WINED3D_SHADER_TYPE_DOMAIN)) && ctx_data->glsl_program)
    {
        ds_id = ctx_data->glsl_program->ds.id;
    }
    else if (dshader)
    {
        struct ds_compile_args args;

        find_ds_compile_args(state, dshader, &args, context);
        ds_id = find_glsl_domain_shader(context, priv, dshader, &args);
    }

    gshader = state->shader[WINED3D_SHADER_TYPE_GEOMETRY];
    if (!(context->shader_update_mask & (1u << WINED3D_SHADER_TYPE_GEOMETRY)) && ctx_data->glsl_program)
    {
        gs_id = ctx_data->glsl_program->gs.id;
    }
    else if (gshader)
    {
        struct gs_compile_args args;

        find_gs_compile_args(state, gshader, &args, context);
        gs_id = find_glsl_geometry_shader(context, priv, gshader, &args);
    }

    /* A pixel shader is not used when rasterization is disabled. */
    if (is_rasterization_disabled(gshader))
    {
        ps_id = 0;
        ps_list = NULL;
    }
    else if (!(context->shader_update_mask & (1u << WINED3D_SHADER_TYPE_PIXEL)) && ctx_data->glsl_program)
    {
        ps_id = ctx_data->glsl_program->ps.id;
        ps_list = &ctx_data->glsl_program->ps.shader_entry;

        if (use_ps(state))
            pshader = state->shader[WINED3D_SHADER_TYPE_PIXEL];
    }
    else if (use_ps(state))
    {
        struct ps_compile_args ps_compile_args;
        pshader = state->shader[WINED3D_SHADER_TYPE_PIXEL];
        find_ps_compile_args(state, pshader, context->stream_info.position_transformed, &ps_compile_args, context);
        ps_id = find_glsl_pshader(context, &priv->shader_buffer, &priv->string_buffers,
                pshader, &ps_compile_args, &np2fixup_info);
        ps_list = &pshader->linked_programs;
    }
    else if (priv->fragment_pipe == &glsl_fragment_pipe
            && !(vshader && vshader->reg_maps.shader_version.major >= 4))
    {
        struct glsl_ffp_fragment_shader *ffp_shader;
        struct ffp_frag_settings settings;

        gen_ffp_frag_op(context, state, &settings, FALSE);
        ffp_shader = shader_glsl_find_ffp_fragment_shader(priv, &settings, context);
        ps_id = ffp_shader->id;
        ps_list = &ffp_shader->linked_programs;
    }

    key.vs_id = vs_id;
    key.hs_id = hs_id;
    key.ds_id = ds_id;
    key.gs_id = gs_id;
    key.ps_id = ps_id;
    key.cs_id = 0;
    if ((!vs_id && !hs_id && !ds_id && !gs_id && !ps_id) || (entry = get_glsl_program_entry(priv, &key)))
    {
        ctx_data->glsl_program = entry;
        return;
    }

    /* If we get to this point, then no matching program exists, so we create one */
    program_id = GL_EXTCALL(glCreateProgram());
    TRACE("Created new GLSL shader program %u.\n", program_id);

    /* Create the entry */
    entry = heap_alloc(sizeof(*entry));
    entry->id = program_id;
    entry->vs.id = vs_id;
    entry->hs.id = hs_id;
    entry->ds.id = ds_id;
    entry->gs.id = gs_id;
    entry->ps.id = ps_id;
    entry->cs.id = 0;
    entry->constant_version = 0;
    entry->shader_controlled_clip_distances = 0;
    entry->ps.np2_fixup_info = np2fixup_info;
    /* Add the hash table entry */
    add_glsl_program_entry(priv, entry);

    /* Set the current program */
    ctx_data->glsl_program = entry;

    /* Attach GLSL vshader */
    if (vs_id)
    {
        TRACE("Attaching GLSL shader object %u to program %u.\n", vs_id, program_id);
        GL_EXTCALL(glAttachShader(program_id, vs_id));
        checkGLcall("glAttachShader");

        list_add_head(vs_list, &entry->vs.shader_entry);
    }

    if (vshader)
    {
        attribs_map = vshader->reg_maps.input_registers;
        if (vshader->reg_maps.shader_version.major < 4)
        {
            reorder_shader_id = shader_glsl_generate_vs3_rasterizer_input_setup(priv, vshader, pshader,
                    state->gl_primitive_type == GL_POINTS && vshader->reg_maps.point_size,
                    d3d_info->emulated_flatshading
                    && state->render_states[WINED3D_RS_SHADEMODE] == WINED3D_SHADE_FLAT, gl_info);
            TRACE("Attaching GLSL shader object %u to program %u.\n", reorder_shader_id, program_id);
            GL_EXTCALL(glAttachShader(program_id, reorder_shader_id));
            checkGLcall("glAttachShader");
            /* Flag the reorder function for deletion, it will be freed
             * automatically when the program is destroyed. */
            GL_EXTCALL(glDeleteShader(reorder_shader_id));
        }
    }
    else
    {
        attribs_map = (1u << WINED3D_FFP_ATTRIBS_COUNT) - 1;
    }

    if (!shader_glsl_use_explicit_attrib_location(gl_info))
    {
        /* Bind vertex attributes to a corresponding index number to match
         * the same index numbers as ARB_vertex_programs (makes loading
         * vertex attributes simpler). With this method, we can use the
         * exact same code to load the attributes later for both ARB and
         * GLSL shaders.
         *
         * We have to do this here because we need to know the Program ID
         * in order to make the bindings work, and it has to be done prior
         * to linking the GLSL program. */
        tmp_name = string_buffer_get(&priv->string_buffers);
        for (i = 0; attribs_map; attribs_map >>= 1, ++i)
        {
            if (!(attribs_map & 1))
                continue;

            string_buffer_sprintf(tmp_name, "vs_in%u", i);
            GL_EXTCALL(glBindAttribLocation(program_id, i, tmp_name->buffer));
            if (vshader && vshader->reg_maps.shader_version.major >= 4)
            {
                string_buffer_sprintf(tmp_name, "vs_in_uint%u", i);
                GL_EXTCALL(glBindAttribLocation(program_id, i, tmp_name->buffer));
                string_buffer_sprintf(tmp_name, "vs_in_int%u", i);
                GL_EXTCALL(glBindAttribLocation(program_id, i, tmp_name->buffer));
            }
        }
        checkGLcall("glBindAttribLocation");
        string_buffer_release(&priv->string_buffers, tmp_name);

        if (!needs_legacy_glsl_syntax(gl_info))
        {
            char var[12];

            if (wined3d_dualblend_enabled(state, gl_info))
            {
                for (i = 0; i < gl_info->limits.dual_buffers * 2; i++)
                {
                    sprintf(var, "ps_out%u", i);
                    GL_EXTCALL(glBindFragDataLocationIndexed(program_id, i / 2, i % 2, var));
                    checkGLcall("glBindFragDataLocationIndexed");
                }
            }
            else
            {
                for (i = 0; i < gl_info->limits.buffers; i++)
                {
                    sprintf(var, "ps_out%u", i);
                    GL_EXTCALL(glBindFragDataLocation(program_id, i, var));
                    checkGLcall("glBindFragDataLocation");
                }
            }
        }
    }

    if (hshader)
    {
        TRACE("Attaching GLSL tessellation control shader object %u to program %u.\n", hs_id, program_id);
        GL_EXTCALL(glAttachShader(program_id, hs_id));
        checkGLcall("glAttachShader");

        list_add_head(&hshader->linked_programs, &entry->hs.shader_entry);
    }

    if (dshader)
    {
        TRACE("Attaching GLSL tessellation evaluation shader object %u to program %u.\n", ds_id, program_id);
        GL_EXTCALL(glAttachShader(program_id, ds_id));
        checkGLcall("glAttachShader");

        list_add_head(&dshader->linked_programs, &entry->ds.shader_entry);
    }

    if (gshader)
    {
        TRACE("Attaching GLSL geometry shader object %u to program %u.\n", gs_id, program_id);
        GL_EXTCALL(glAttachShader(program_id, gs_id));
        checkGLcall("glAttachShader");

        shader_glsl_init_transform_feedback(context, priv, program_id, gshader);

        list_add_head(&gshader->linked_programs, &entry->gs.shader_entry);
    }

    /* Attach GLSL pshader */
    if (ps_id)
    {
        TRACE("Attaching GLSL shader object %u to program %u.\n", ps_id, program_id);
        GL_EXTCALL(glAttachShader(program_id, ps_id));
        checkGLcall("glAttachShader");

        list_add_head(ps_list, &entry->ps.shader_entry);
    }

    /* Link the program */
    TRACE("Linking GLSL shader program %u.\n", program_id);
    GL_EXTCALL(glLinkProgram(program_id));
    shader_glsl_validate_link(gl_info, program_id);

    shader_glsl_init_vs_uniform_locations(gl_info, priv, program_id, &entry->vs,
            vshader ? vshader->limits->constant_float : 0);
    shader_glsl_init_ds_uniform_locations(gl_info, priv, program_id, &entry->ds);
    shader_glsl_init_gs_uniform_locations(gl_info, priv, program_id, &entry->gs);
    shader_glsl_init_ps_uniform_locations(gl_info, priv, program_id, &entry->ps,
            pshader ? pshader->limits->constant_float : 0);
    checkGLcall("find glsl program uniform locations");

    pre_rasterization_shader = gshader ? gshader : dshader ? dshader : vshader;
    if (pre_rasterization_shader && pre_rasterization_shader->reg_maps.shader_version.major >= 4)
    {
        unsigned int clip_distance_count = wined3d_popcount(pre_rasterization_shader->reg_maps.clip_distance_mask);
        entry->shader_controlled_clip_distances = 1;
        entry->clip_distance_mask = (1u << clip_distance_count) - 1;
    }

    if (needs_legacy_glsl_syntax(gl_info))
    {
        if (pshader && pshader->reg_maps.shader_version.major >= 3
                && pshader->u.ps.declared_in_count > vec4_varyings(3, gl_info))
        {
            TRACE("Shader %d needs vertex color clamping disabled.\n", program_id);
            entry->vs.vertex_color_clamp = GL_FALSE;
        }
        else
        {
            entry->vs.vertex_color_clamp = GL_FIXED_ONLY_ARB;
        }
    }
    else
    {
        /* With core profile we never change vertex_color_clamp from
         * GL_FIXED_ONLY_MODE (which is also the initial value) so we never call
         * glClampColorARB(). */
        entry->vs.vertex_color_clamp = GL_FIXED_ONLY_ARB;
    }

    /* Set the shader to allow uniform loading on it */
    GL_EXTCALL(glUseProgram(program_id));
    checkGLcall("glUseProgram");

    entry->constant_update_mask = 0;
    if (vshader)
    {
        entry->constant_update_mask |= WINED3D_SHADER_CONST_VS_F;
        if (vshader->reg_maps.integer_constants)
            entry->constant_update_mask |= WINED3D_SHADER_CONST_VS_I;
        if (vshader->reg_maps.boolean_constants)
            entry->constant_update_mask |= WINED3D_SHADER_CONST_VS_B;
        if (entry->vs.pos_fixup_location != -1)
            entry->constant_update_mask |= WINED3D_SHADER_CONST_POS_FIXUP;

        shader_glsl_load_program_resources(context, priv, program_id, vshader);
    }
    else
    {
        entry->constant_update_mask |= WINED3D_SHADER_CONST_FFP_MODELVIEW
                | WINED3D_SHADER_CONST_FFP_PROJ;

        for (i = 1; i < MAX_VERTEX_INDEX_BLENDS; ++i)
        {
            if (entry->vs.modelview_matrix_location[i] != -1)
            {
                entry->constant_update_mask |= WINED3D_SHADER_CONST_FFP_VERTEXBLEND;
                break;
            }
        }

        for (i = 0; i < MAX_TEXTURES; ++i)
        {
            if (entry->vs.texture_matrix_location[i] != -1)
            {
                entry->constant_update_mask |= WINED3D_SHADER_CONST_FFP_TEXMATRIX;
                break;
            }
        }
        if (entry->vs.material_ambient_location != -1 || entry->vs.material_diffuse_location != -1
                || entry->vs.material_specular_location != -1
                || entry->vs.material_emissive_location != -1
                || entry->vs.material_shininess_location != -1)
            entry->constant_update_mask |= WINED3D_SHADER_CONST_FFP_MATERIAL;
        if (entry->vs.light_ambient_location != -1)
            entry->constant_update_mask |= WINED3D_SHADER_CONST_FFP_LIGHTS;
    }
    if (entry->vs.clip_planes_location != -1)
        entry->constant_update_mask |= WINED3D_SHADER_CONST_VS_CLIP_PLANES;
    if (entry->vs.pointsize_min_location != -1)
        entry->constant_update_mask |= WINED3D_SHADER_CONST_VS_POINTSIZE;

    if (hshader)
        shader_glsl_load_program_resources(context, priv, program_id, hshader);

    if (dshader)
    {
        if (entry->ds.pos_fixup_location != -1)
            entry->constant_update_mask |= WINED3D_SHADER_CONST_POS_FIXUP;

        shader_glsl_load_program_resources(context, priv, program_id, dshader);
    }

    if (gshader)
    {
        if (entry->gs.pos_fixup_location != -1)
            entry->constant_update_mask |= WINED3D_SHADER_CONST_POS_FIXUP;

        shader_glsl_load_program_resources(context, priv, program_id, gshader);
    }

    if (ps_id)
    {
        if (pshader)
        {
            entry->constant_update_mask |= WINED3D_SHADER_CONST_PS_F;
            if (pshader->reg_maps.integer_constants)
                entry->constant_update_mask |= WINED3D_SHADER_CONST_PS_I;
            if (pshader->reg_maps.boolean_constants)
                entry->constant_update_mask |= WINED3D_SHADER_CONST_PS_B;
            if (entry->ps.ycorrection_location != -1)
                entry->constant_update_mask |= WINED3D_SHADER_CONST_PS_Y_CORR;

            shader_glsl_load_program_resources(context, priv, program_id, pshader);
            shader_glsl_load_images(gl_info, priv, program_id, &pshader->reg_maps);
        }
        else
        {
            entry->constant_update_mask |= WINED3D_SHADER_CONST_FFP_PS;

            shader_glsl_load_samplers(context, priv, program_id, NULL);
        }

        for (i = 0; i < MAX_TEXTURES; ++i)
        {
            if (entry->ps.bumpenv_mat_location[i] != -1)
            {
                entry->constant_update_mask |= WINED3D_SHADER_CONST_PS_BUMP_ENV;
                break;
            }
        }

        if (entry->ps.fog_color_location != -1)
            entry->constant_update_mask |= WINED3D_SHADER_CONST_PS_FOG;
        if (entry->ps.alpha_test_ref_location != -1)
            entry->constant_update_mask |= WINED3D_SHADER_CONST_PS_ALPHA_TEST;
        if (entry->ps.np2_fixup_location != -1)
            entry->constant_update_mask |= WINED3D_SHADER_CONST_PS_NP2_FIXUP;
        if (entry->ps.color_key_location != -1)
            entry->constant_update_mask |= WINED3D_SHADER_CONST_FFP_COLOR_KEY;
    }
}