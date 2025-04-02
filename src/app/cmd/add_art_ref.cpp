#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#include "app/cmd/add_art_ref.h"

#include "app/doc.h"
#include "app/doc_event.h"
#include "doc/art_ref.h"
#include "doc/art_ref_io.h"
#include "doc/sprite.h"

namespace app { namespace cmd {

using namespace doc;

AddArtRef::AddArtRef(Sprite* sprite, ArtRef* artRef) : WithSprite(sprite), WithArtRef(artRef), m_size(0)
{
}

void AddArtRef::onExecute()
{
  Sprite* sprite = this->sprite();
  ArtRef* artRef = this->artRef();

  addArtRef(sprite, artRef);
}

void AddArtRef::onUndo()
{
  Sprite* sprite = this->sprite();
  ArtRef* artRef = this->artRef();
  write_art_ref(m_stream, artRef);
  m_size = size_t(m_stream.tellp());

  removeArtRef(sprite, artRef);
}

void AddArtRef::onRedo()
{
  Sprite* sprite = this->sprite();
  ArtRef* artRef = read_art_ref(m_stream);

  addArtRef(sprite, artRef);

  m_stream.str(std::string());
  m_stream.clear();
  m_size = 0;
}

void AddArtRef::addArtRef(Sprite* sprite, ArtRef* artRef)
{
  sprite->artRefs().add(artRef);
  sprite->incrementVersion();

  /*
  Doc* doc = static_cast<Doc*>(sprite->document());
  DocEvent ev(doc);
  ev.sprite(sprite);
  ev.artRef(artRef);
  doc->notify_observers<DocEvent&>(&DocObserver::onAddArtRef, ev);
  */
}

void AddArtRef::removeArtRef(Sprite* sprite, ArtRef* artRef)
{
  /*
  Doc* doc = static_cast<Doc*>(sprite->document());
  DocEvent ev(doc);
  ev.sprite(sprite);
  ev.artRef(artRef);
  doc->notify_observers<DocEvent&>(&DocObserver::onRemoveArtRef, ev);
  */

  sprite->artRefs().remove(artRef);
  sprite->incrementVersion();
  delete artRef;
}

}} // namespace app::cmd
