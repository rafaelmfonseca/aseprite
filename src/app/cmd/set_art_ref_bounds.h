#ifndef APP_CMD_SET_ART_REF_BOUNDS_H_INCLUDED
#define APP_CMD_SET_ART_REF_BOUNDS_H_INCLUDED
#pragma once

#include "app/cmd.h"
#include "app/cmd/with_art_ref.h"
#include "gfx/rect.h"
#include "doc/art_ref.h"

namespace app { namespace cmd {
using namespace doc;

class SetArtRefBoundsF : public Cmd,
                         public WithArtRef {
public:
  SetArtRefBoundsF(ArtRef* artRef, const gfx::RectF& oldBounds);

protected:
  void onExecute() override;
  void onUndo() override;
  size_t onMemSize() const override { return sizeof(*this); }

private:
  doc::ArtRef m_artRef;

  gfx::RectF m_oldBounds;
  gfx::RectF m_newBounds;
};

}} // namespace app::cmd

#endif
