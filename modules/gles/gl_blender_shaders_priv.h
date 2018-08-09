/*
 * gl_blender_shaders_priv.h - gl blender shaders private class
 *
 *  Copyright (c) 2018 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Yinhang Liu <yinhangx.liu@intel.com>
 */

#ifndef XCAM_GL_BLENDER_SHADERS_PRIV_H
#define XCAM_GL_BLENDER_SHADERS_PRIV_H

#include <interface/data_types.h>
#include <gles/gl_image_shader.h>
#include <gles/gl_image_handler.h>
#include <gles/gl_buffer.h>

#define GL_BLENDER_ALIGN_X 8
#define GL_BLENDER_ALIGN_Y 4

enum BufIdx {
    Idx0 = 0,
    Idx1,
    BufIdxCount
};

namespace XCam {

namespace XCamGLShaders {

class GLGaussScalePyrShader
    : public GLImageShader
{
public:
    struct Args : GLArgs {
        SmartPtr<GLBuffer>         in_glbuf;
        SmartPtr<GLBuffer>         out_glbuf;
        Rect                       merge_area;

        const uint32_t             level;
        const BufIdx               idx;
        SmartPtr<VideoBuffer>      out_video_buf;

        Args (
            const SmartPtr<ImageHandler::Parameters> &param,
            uint32_t l, BufIdx i)
            : GLArgs (param)
            , level (l)
            , idx (i)
        {}
    };

public:
    explicit GLGaussScalePyrShader (const SmartPtr<Worker::Callback> &cb)
        : GLImageShader ("GLGaussScalePyrShader", cb)
    {}

private:
    virtual XCamReturn prepare_arguments (const SmartPtr<Worker::Arguments> &args, GLCmdList &cmds);
    bool check_desc (const GLBufferDesc &in_desc, const GLBufferDesc &out_desc, const Rect &merge_area);
};

class GLLapTransPyrShader
    : public GLImageShader
{
public:
    struct Args : GLArgs {
        SmartPtr<GLBuffer>         in_glbuf;
        SmartPtr<GLBuffer>         out_glbuf;
        SmartPtr<GLBuffer>         gaussscale_glbuf;
        Rect                       merge_area;

        const uint32_t             level;
        const BufIdx               idx;
        SmartPtr<VideoBuffer>      out_video_buf;

        Args (
            const SmartPtr<ImageHandler::Parameters> &param,
            uint32_t l, BufIdx i)
            : GLArgs (param)
            , level (l)
            , idx (i)
        {}
    };

public:
    explicit GLLapTransPyrShader (const SmartPtr<Worker::Callback> &cb)
        : GLImageShader ("GLLapTransPyrShader", cb)
    {}

private:
    virtual XCamReturn prepare_arguments (const SmartPtr<Worker::Arguments> &args, GLCmdList &cmds);
    bool check_desc (
        const GLBufferDesc &in_desc, const GLBufferDesc &out_desc,
        const GLBufferDesc &gs_desc, const Rect &merge_area);
};

SmartPtr<GLGaussScalePyrShader>
create_gauss_scale_pyr_shader (SmartPtr<Worker::Callback> &cb);

SmartPtr<GLLapTransPyrShader>
create_lap_trans_pyr_shader (SmartPtr<Worker::Callback> &cb);

}

}

#endif // XCAM_GL_BLENDER_SHADERS_PRIV_H