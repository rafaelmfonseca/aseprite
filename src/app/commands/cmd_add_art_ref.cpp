#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#include "app/commands/cmd_add_art_ref.h"

#include "app/doc_api.h"
#include "doc/art_ref.h"
#include "app/cmd/add_art_ref.h"
#include "app/tx.h"
#include "app/ui/editor/editor.h"
#include "app/commands/new_params.h"
#include "app/modules/gui.h"
#include "base/base64.h"
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

  // Pixel position to get
  gfx::PointF pixelPos = editor->screenToEditorF(mousePos);

  ArtRef* artRef = new ArtRef;

  // TODO rafaelmfonseca: revisit logic
  // START: temporary logic
  static const char alphanum[] =
      "0123456789"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz";
  std::string tmp_s;
  tmp_s.reserve(10);

  for (int i = 0; i < 10; ++i) {
      tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
  }
  // END: temporary logic

  artRef->setName(tmp_s);
  artRef->setBounds(gfx::Rect(pixelPos.x, pixelPos.y, 4, 4));

  ContextWriter writer(context);
  Doc* document(writer.document());
  Sprite* sprite(writer.sprite());

  {
    Tx tx(writer, "Add Art Ref");
    tx(new cmd::AddArtRef(sprite, artRef));
    tx.commit();
  }

  update_screen_for_document(document);
}

Command* CommandFactory::createAddArtRefCommand()
{
  return new AddArtRefCommand;
}

} // namespace app