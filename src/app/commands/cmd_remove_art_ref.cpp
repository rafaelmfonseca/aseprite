#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#include "app/app.h"
#include "app/cmd/remove_art_ref.h"
#include "app/commands/command.h"
#include "app/context_access.h"
#include "app/i18n/strings.h"
#include "app/modules/gui.h"
#include "app/tx.h"
#include "app/ui/status_bar.h"
#include "base/convert_to.h"
#include "doc/selected_objects.h"
#include "doc/art_ref.h"
#include "doc/sprite.h"
#include "ui/alert.h"
#include "ui/widget.h"

namespace app {

class RemoveArtRefCommand : public Command {
public:
  RemoveArtRefCommand();

protected:
  void onLoadParams(const Params& params) override;
  bool onEnabled(Context* context) override;
  void onExecute(Context* context) override;

private:
  std::string m_ArtRefName;
  ObjectId m_artRefId;
};

RemoveArtRefCommand::RemoveArtRefCommand() : Command(CommandId::RemoveArtRef(), CmdRecordableFlag)
{
}

void RemoveArtRefCommand::onLoadParams(const Params& params)
{
  m_ArtRefName = params.get("name");

  std::string id = params.get("id");
  if (!id.empty())
    m_artRefId = ObjectId(base::convert_to<doc::ObjectId>(id));
  else
    m_artRefId = NullId;
}

bool RemoveArtRefCommand::onEnabled(Context* context)
{
  return context->checkFlags(ContextFlags::ActiveDocumentIsWritable |
                             ContextFlags::HasActiveSprite | ContextFlags::HasActiveLayer);
}

void RemoveArtRefCommand::onExecute(Context* context)
{
  const ContextReader reader(context);
  const Sprite* sprite = reader.sprite();
  frame_t frame = reader.frame();
  SelectedObjects artRefsToDelete;

  std::string artRefName;
  {
    ArtRef* artRef = nullptr;
    if (!m_ArtRefName.empty())
      artRef = sprite->artRefs().getByName(m_ArtRefName);
    else if (m_artRefId != NullId)
      artRef = sprite->artRefs().getById(m_artRefId);

    if (artRef)
      artRefsToDelete.insert(artRef->id());
    else
      artRefsToDelete = reader.site()->selectedArtRefs();
  }

  // Nothing to delete
  if (artRefsToDelete.empty())
    return;

  if (artRefsToDelete.size() == 1) {
    ArtRef* artRef = artRefsToDelete.frontAs<ArtRef>();
    ASSERT(artRef);
    if (artRef)
      artRefName = artRef->name();
  }

  {
    ContextWriter writer(reader);
    Doc* document(writer.document());
    Sprite* sprite(writer.sprite());
    Tx tx(writer, "Remove Art Ref");

    for (auto artRef : artRefsToDelete.iterateAs<ArtRef>()) {
      ASSERT(artRef);
      if (!artRef)
        continue;

      tx(new cmd::RemoveArtRef(sprite, artRef));
    }

    tx.commit();
    document->notifyGeneralUpdate();
  }
}

Command* CommandFactory::createRemoveArtRefCommand()
{
  return new RemoveArtRefCommand;
}

} // namespace app
