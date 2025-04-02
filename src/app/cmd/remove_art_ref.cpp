#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#include "app/cmd/remove_art_ref.h"

namespace app { namespace cmd {

using namespace doc;

RemoveArtRef::RemoveArtRef(Sprite* sprite, ArtRef* artRef) : AddArtRef(sprite, artRef)
{
}

void RemoveArtRef::onExecute()
{
  AddArtRef::onUndo();
}

void RemoveArtRef::onUndo()
{
  AddArtRef::onRedo();
}

void RemoveArtRef::onRedo()
{
  AddArtRef::onUndo();
}

}} // namespace app::cmd
