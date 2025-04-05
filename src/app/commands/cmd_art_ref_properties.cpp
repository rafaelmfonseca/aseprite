#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#include "app/commands/command.h"
#include "app/modules/gui.h"
#include "app/context_access.h"
#include "app/tx.h"
#include "app/i18n/strings.h"
#include "base/convert_to.h"
#include "doc/art_ref.h"
#include "doc/sprite.h"
#include "app/ui/skin/skin_theme.h"
#include "ui/box.h"
#include "ui/button.h"
#include "ui/label.h"
#include "ui/entry.h"
#include "ui/slider.h"
#include "ui/tooltips.h"
#include "ui/widget.h"
#include "ui/separator.h"
#include "ui/window.h"

namespace app {

using namespace ui;

class ArtRefPropertiesWindow : public ui::Window {
public:
  ArtRefPropertiesWindow(const ContextReader& reader,
                         const doc::SelectedObjects& artRefs)
    : Window(Window::WithTitleBar, Strings::art_ref_properties_title())
  {
    ASSERT(!artRefs.empty());

    ArtRef* artRef = artRefs.frontAs<ArtRef>();

    if (artRefs.size() == 1) {
      ArtRef* artRef = artRefs.frontAs<ArtRef>();

      auto box1 = new Box(VERTICAL);
      auto box2 = new Box(VERTICAL);
      auto box3 = new Box(HORIZONTAL | HOMOGENEOUS);

      auto label_color = new Label(Strings::art_ref_properties_text());

      auto entry_text = new Entry(strtol("255", nullptr, 10), "");
      entry_text->setText(artRef->name());
      //entry_text->Change.connect([this, entry, mod] { onModifyField(entry, mod); });

      m_buttonOk = new Button(Strings::art_ref_properties_ok());
      auto button_cancel = new Button(Strings::art_ref_properties_cancel());

      auto sep = new Separator("", HORIZONTAL);
      sep->InitTheme.connect([sep] {
        auto theme = skin::SkinTheme::get(sep);
        sep->setBorder(sep->border() + gfx::Border(0, 8, 0, 8) * guiscale());
      });
      sep->initTheme();

      m_buttonOk->processMnemonicFromText();
      button_cancel->processMnemonicFromText();

      m_buttonOk->Click.connect([this] { closeWindow(m_buttonOk); });
      button_cancel->Click.connect([this, button_cancel] { closeWindow(button_cancel); });

      addChild(box1);
      box1->addChild(box2);
      box1->addChild(box3);
      box2->addChild(entry_text);
      box2->addChild(sep);
      box3->addChild(button_cancel);
      box3->addChild(m_buttonOk);
    }

    // Default position
    remapWindow();
    centerWindow();
  }

  bool show()
  {
    openWindowInForeground();
    return (closer() == m_buttonOk);
  }

private:
  ui::Button* m_buttonOk;
};

class ArtRefPropertiesCommand : public Command {
public:
  ArtRefPropertiesCommand();

protected:
  void onLoadParams(const Params& params) override;
  bool onEnabled(Context* context) override;
  void onExecute(Context* context) override;

private:
  std::string m_artRefName;
  ObjectId m_artRefId;
};

ArtRefPropertiesCommand::ArtRefPropertiesCommand()
  : Command(CommandId::ArtRefProperties(), CmdUIOnlyFlag)
  , m_artRefId(NullId)
{
}

void ArtRefPropertiesCommand::onLoadParams(const Params& params)
{
  m_artRefName = params.get("name");

  std::string id = params.get("id");
  if (!id.empty())
    m_artRefId = ObjectId(base::convert_to<doc::ObjectId>(id));
  else
    m_artRefId = NullId;
}

bool ArtRefPropertiesCommand::onEnabled(Context* context)
{
  return context->checkFlags(ContextFlags::ActiveDocumentIsWritable);
}

void ArtRefPropertiesCommand::onExecute(Context* context)
{
  const ContextReader reader(context);
  const Sprite* sprite = reader.sprite();
  frame_t frame = reader.frame();
  SelectedObjects artRefs;

  {
    ArtRef* artRef = nullptr;
    if (!m_artRefName.empty())
      artRef = sprite->artRefs().getByName(m_artRefName);
    else if (m_artRefId != NullId)
      artRef = sprite->artRefs().getById(m_artRefId);

    if (artRef)
      artRefs.insert(artRef->id());
    else
      artRefs = reader.site()->selectedArtRefs();
  }

  // Nothing to delete
  if (artRefs.empty())
    return;

  ArtRefPropertiesWindow window(reader, artRefs);
  if (!window.show())
    return;

  {
    /*
    const ArtRefPropertiesWindow::Mods mods = window.modifiedFields();
    ContextWriter writer(reader);
    Tx tx(writer, "Art Ref Properties");

    tx.commit();
    writer.document()->notifyGeneralUpdate();
    */
  }
}

Command* CommandFactory::createArtRefPropertiesCommand()
{
  return new ArtRefPropertiesCommand;
}

} // namespace app
