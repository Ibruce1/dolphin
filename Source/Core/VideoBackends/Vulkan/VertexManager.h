// Copyright 2016 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <memory>
#include <vector>

#include "Common/CommonTypes.h"
#include "VideoCommon/VertexManagerBase.h"

namespace Vulkan
{
class StateTracker;
class StreamBuffer;

class VertexManager : public VertexManagerBase
{
public:
  VertexManager();
  ~VertexManager();

  bool Initialize(StateTracker* state_tracker);

  NativeVertexFormat* CreateNativeVertexFormat(const PortableVertexDeclaration& vtx_decl) override;

protected:
  void PrepareDrawBuffers(u32 stride);
  void ResetBuffer(u32 stride) override;

private:
  void vFlush(bool use_dst_alpha) override;

  StateTracker* m_state_tracker = nullptr;

  std::vector<u8> m_cpu_vertex_buffer;
  std::vector<u16> m_cpu_index_buffer;

  std::unique_ptr<StreamBuffer> m_vertex_stream_buffer;
  std::unique_ptr<StreamBuffer> m_index_stream_buffer;

  u32 m_current_draw_base_vertex = 0;
  u32 m_current_draw_base_index = 0;
};
}
