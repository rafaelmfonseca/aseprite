#ifndef APP_CMD_REMOVE_ART_REF_H_INCLUDED
#define APP_CMD_REMOVE_ART_REF_H_INCLUDED
#pragma once

#include "app/cmd/add_art_ref.h"

namespace app { namespace cmd {
using namespace doc;

class RemoveArtRef : public AddArtRef {
public:
  RemoveArtRef(Sprite* sprite, ArtRef* artRef);

protected:
  void onExecute() override;
  void onUndo() override;
  void onRedo() override;
};

}} // namespace app::cmd

#endif