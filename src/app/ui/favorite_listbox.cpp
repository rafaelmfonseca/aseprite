#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#include "app/ui/favorite_listbox.h"

#include "app/app.h"
#include "app/commands/commands.h"
#include "app/commands/params.h"
#include "app/i18n/strings.h"
#include "app/pref/preferences.h"
#include "app/ui/draggable_widget.h"
#include "app/ui/skin/skin_theme.h"
#include "app/ui_context.h"
#include "app/favorite_folders.h"
#include "base/fs.h"
#include "ui/alert.h"
#include "ui/graphics.h"
#include "ui/link_label.h"
#include "ui/listitem.h"
#include "ui/message.h"
#include "ui/paint_event.h"
#include "ui/scroll_region_event.h"
#include "ui/size_hint_event.h"
#include "ui/system.h"
#include "ui/view.h"

namespace app {

using namespace ui;
using namespace skin;

//////////////////////////////////////////////////////////////////////
// FavoriteItem

class FavoriteItem : public LinkLabel {
public:
  FavoriteItem(const std::string& link, const std::string& title, const std::string& desc)
    : LinkLabel(link, title)
    , m_title(title)
    , m_desc(desc)
  {
    initTheme();
  }

protected:
  void onInitTheme(InitThemeEvent& ev) override
  {
    LinkLabel::onInitTheme(ev);
    auto theme = SkinTheme::get(this);
    setStyle(theme->styles.recentItem());
  }

  void onSizeHint(SizeHintEvent& ev) override
  {
    auto theme = SkinTheme::get(this);
    ui::Style* style = theme->styles.recentFile();

    setTextQuiet(m_title);
    gfx::Size sz = theme->calcSizeHint(this, style);

    if (!m_desc.empty())
      sz.h *= 5;

    ev.setSizeHint(gfx::Size(0, sz.h));
  }

  void onPaint(PaintEvent& ev) override
  {
    auto theme = SkinTheme::get(this);
    Graphics* g = ev.graphics();
    gfx::Rect bounds = clientBounds();
    ui::Style* style = theme->styles.recentFile();
    ui::Style* styleDetail = theme->styles.recentFileDetail();

    setTextQuiet(m_title);
    gfx::Size textSize = theme->calcSizeHint(this, style);
    gfx::Rect textBounds(bounds.x, bounds.y, bounds.w, textSize.h);
    gfx::Rect detailsBounds(bounds.x, bounds.y + textSize.h, bounds.w, bounds.h - textSize.h);

    theme->paintWidget(g, this, style, textBounds);

    setTextQuiet(m_desc);
    theme->paintWidget(g, this, styleDetail, detailsBounds);
  }

  void onClick() override
  {
    // static_cast<FavoriteListBox*>(parent())->onClick(m_title);
  }

private:
  std::string m_title;
  std::string m_desc;
};

//////////////////////////////////////////////////////////////////////
// FavoriteListBox

FavoriteListBox::FavoriteListBox()
{
  // App::instance()->favoriteFolders()->Changed.connect([this] { rebuildList(); });
  reload();
}

void FavoriteListBox::reload()
{
  while (auto child = lastChild()) {
    removeChild(child);
  }

  auto recent = App::instance()->favoriteFolders();
  for (const auto& fn : recent->favoriteFolders()) {
    addChild(new LinkLabel(fn->label()));
    for (const auto& file : fn->listFiles()) {
      addChild(new LinkLabel(file));
      //addChild(new FavoriteItem(fn->label(), file, fn->label()));
    }
  }

  View* view = View::getView(this);
  if (view)
    view->updateView();
}

} // namespace app
