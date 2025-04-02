#ifndef APP_CMD_ADD_ART_REF_H_INCLUDED
#define APP_CMD_ADD_ART_REF_H_INCLUDED
#pragma once

#include "app/cmd.h"
#include "app/commands/command.h"
#include "app/cmd/with_art_ref.h"
#include "app/cmd/with_sprite.h"
#include "gfx/point.h"

#include <sstream>

namespace app { namespace cmd {
using namespace doc;

class AddArtRef : public Cmd,
                  public WithSprite,
                  public WithArtRef {
public:
  AddArtRef(Sprite* sprite, ArtRef* artRef);

protected:
  void onExecute() override;
  void onUndo() override;
  void onRedo() override;
  size_t onMemSize() const override { return sizeof(*this) + m_size; }

private:
  void addArtRef(Sprite* sprite, ArtRef* artRef);
  void removeArtRef(Sprite* sprite, ArtRef* artRef);

  size_t m_size;
  std::stringstream m_stream;
};

}} // namespace app::cmd

#endif