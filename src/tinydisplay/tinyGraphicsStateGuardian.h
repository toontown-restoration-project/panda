// Filename: tinyGraphicsStateGuardian.h
// Created by:  drose (24Apr08)
//
////////////////////////////////////////////////////////////////////
//
// PANDA 3D SOFTWARE
// Copyright (c) 2001 - 2004, Disney Enterprises, Inc.  All rights reserved
//
// All use of this software is subject to the terms of the Panda 3d
// Software license.  You should have received a copy of this license
// along with this source code; you will also find a current copy of
// the license at http://etc.cmu.edu/panda3d/docs/license/ .
//
// To contact the maintainers of this program write to
// panda3d-general@lists.sourceforge.net .
//
////////////////////////////////////////////////////////////////////

#ifndef TINYGRAPHICSSTATEGUARDIAN_H
#define TINYGRAPHICSSTATEGUARDIAN_H

#include "pandabase.h"

#include "graphicsStateGuardian.h"
#include "tinyGraphicsPipe.h"
#include "tinygl.h"

extern "C" {
  #include "zmath.h"
}

class TinyTextureContext;
struct GLContext;
struct GLVertex;
struct GLImage;


////////////////////////////////////////////////////////////////////
//       Class : TinyGraphicsStateGuardian
// Description : An interface to TinySDGL (an implementation of TinyGL
//               over SDL).
////////////////////////////////////////////////////////////////////
class TinyGraphicsStateGuardian : public GraphicsStateGuardian {
public:
  TinyGraphicsStateGuardian(GraphicsPipe *pipe,
                            TinyGraphicsStateGuardian *share_with);

  virtual ~TinyGraphicsStateGuardian();

  virtual void reset();
  virtual void free_pointers();

  virtual PT(GeomMunger) make_geom_munger(const RenderState *state,
                                          Thread *current_thread);

  virtual void clear(DrawableRegion *clearable);

  virtual void prepare_display_region(DisplayRegionPipelineReader *dr,
                                      Lens::StereoChannel stereo_channel);
  virtual CPT(TransformState) calc_projection_mat(const Lens *lens);
  virtual bool prepare_lens();

  virtual bool begin_frame(Thread *current_thread);
  virtual bool begin_scene();
  virtual void end_scene();
  virtual void end_frame(Thread *current_thread);

  virtual bool begin_draw_primitives(const GeomPipelineReader *geom_reader,
                                     const GeomMunger *munger,
                                     const GeomVertexDataPipelineReader *data_reader,
                                     bool force);
  virtual bool draw_triangles(const GeomPrimitivePipelineReader *reader,
                              bool force);
  virtual bool draw_lines(const GeomPrimitivePipelineReader *reader,
                          bool force);
  virtual bool draw_points(const GeomPrimitivePipelineReader *reader,
                           bool force);
  virtual void end_draw_primitives();

  virtual void framebuffer_copy_to_texture
  (Texture *tex, int z, const DisplayRegion *dr, const RenderBuffer &rb);
  virtual bool framebuffer_copy_to_ram
  (Texture *tex, int z, const DisplayRegion *dr, const RenderBuffer &rb);

  virtual void set_state_and_transform(const RenderState *state,
                                       const TransformState *transform);

  virtual TextureContext *prepare_texture(Texture *tex);
  virtual void release_texture(TextureContext *tc);

  virtual void enable_lighting(bool enable);
  virtual void set_ambient_light(const Colorf &color);
  virtual void enable_light(int light_id, bool enable);
  virtual void begin_bind_lights();
  virtual void end_bind_lights();

private:
  void do_issue_transform();
  void do_issue_render_mode();
  void do_issue_cull_face();
  void do_issue_material();
  void do_issue_texture();
  void do_issue_blending();

  void apply_texture(TextureContext *tc);
  bool upload_texture(TinyTextureContext *gtc);

  static void copy_lum_image(GLImage *im, Texture *tex);
  static void copy_alpha_image(GLImage *im, Texture *tex);
  static void copy_one_channel_image(GLImage *im, Texture *tex, int channel);
  static void copy_la_image(GLImage *im, Texture *tex);
  static void copy_rgb_image(GLImage *im, Texture *tex);
  static void copy_rgba_image(GLImage *im, Texture *tex);

  static void load_matrix(M4 *matrix, const TransformState *transform);

  INLINE static GLenum get_light_id(int index);

private:
  GLContext *_c;

  // Used during being_draw_primitives() .. end_draw_primitives().
  int _min_vertex;
  int _max_vertex;
  GLVertex *_vertices;
  int _vertices_size;

  static PStatCollector _vertices_immediate_pcollector;

public:
  static TypeHandle get_class_type() {
    return _type_handle;
  }
  static void init_type() {
    GraphicsStateGuardian::init_type();
    register_type(_type_handle, "TinyGraphicsStateGuardian",
                  GraphicsStateGuardian::get_class_type());
  }
  virtual TypeHandle get_type() const {
    return get_class_type();
  }
  virtual TypeHandle force_init_type() {init_type(); return get_class_type();}

private:
  static TypeHandle _type_handle;
};

#include "tinyGraphicsStateGuardian.I"

#endif