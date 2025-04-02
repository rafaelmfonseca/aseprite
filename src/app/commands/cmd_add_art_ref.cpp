#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#include "app/commands/cmd_add_art_ref.h"

#include "app/doc_api.h"
#include "doc/art_ref.h"
#include "doc/sprite.h"
#include "app/cmd/add_art_ref.h"
#include "app/tx.h"
#include "app/ui/editor/editor.h"
#include "app/commands/new_params.h"
#include "app/modules/gui.h"
#include "base/base64.h"
#include "fmt/format.h"
#include "ui/alert.h"

namespace app {

AddArtRefCommand::AddArtRefCommand() : Command(CommandId::AddArtRef(), CmdUIOnlyFlag)
{
}

bool AddArtRefCommand::onEnabled(Context* context)
{
  return context->checkFlags(ContextFlags::ActiveDocumentIsWritable |
                             ContextFlags::HasActiveSprite);
}

void AddArtRefCommand::onExecute(Context* context)
{
  
}

void AddArtRefCommand::executeOnMousePos(Context* context,
                                         Editor* editor,
                                         const gfx::Point& mousePos)
{
  ASSERT(editor);

  ContextWriter writer(context);
  Doc* document(writer.document());
  Sprite* sprite(writer.sprite());

  // Pixel position to get
  gfx::PointF pixelPos = editor->screenToEditorF(mousePos);

  {
    Tx tx(writer, "Add Art Ref");

    ArtRef* artRef = new ArtRef;
    artRef->setName(getUniqueArtRefName(sprite));
    artRef->setBounds(gfx::Rect(pixelPos.x, pixelPos.y, 4, 4));

    tx(new cmd::AddArtRef(sprite, artRef));
    tx.commit();
  }

  if (context->isUIAvailable()) {
    update_screen_for_document(document);
  }
}

std::string AddArtRefCommand::getUniqueArtRefName(const doc::Sprite* sprite) const
{
  std::string prefix = "ArtRef";
  int max = 0;

  for (ArtRef* artRef : sprite->artRefs())
    if (std::strncmp(artRef->name().c_str(), prefix.c_str(), prefix.size()) == 0)
      max = std::max(max, (int)std::strtol(artRef->name().c_str() + prefix.size(), nullptr, 10));

  return fmt::format("{} {}", prefix, max + 1);
}

Command* CommandFactory::createAddArtRefCommand()
{
  return new AddArtRefCommand;
}

} // namespace app