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
#include "app/ui/separator_in_view.h"
#include "app/ui/skin/skin_theme.h"
#include "app/ui_context.h"
#include "app/favorite_folders.h"
#include "base/fs.h"
#include "ui/alert.h"
#include "ui/graphics.h"
#include "ui/link_label.h"
#include "ui/listitem.h"
#include "ui/message.h"
#include "ui/separator.h"
#include "ui/paint_event.h"
#include "ui/scroll_region_event.h"
#include "ui/size_hint_event.h"
#include "ui/system.h"
#include "ui/view.h"

namespace app {

using namespace ui;
using namespace skin;

//////////////////////////////////////////////////////////////////////
// FavoriteItemSeparator

class FavoriteItemSeparator : public Separator {
public:
  FavoriteItemSeparator(const std::string& text)
    : Separator(text, ui::HORIZONTAL) { }
};

//////////////////////////////////////////////////////////////////////
// FavoriteItem

class FavoriteItem : public LinkLabel {
public:
  FavoriteItem(const std::string& file)
    : LinkLabel("", "")
    , m_fullpath(file)
    , m_name(base::get_file_name(file))
    , m_path(base::get_file_path(file))
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
    ui::Style* styleDetail = theme->styles.recentFileDetail();

    setTextQuiet(m_name);
    gfx::Size sz1 = theme->calcSizeHint(this, style);

    setTextQuiet(m_fullpath);
    gfx::Size sz2 = theme->calcSizeHint(this, styleDetail);

    ev.setSizeHint(gfx::Size(sz1.w + sz2.w, std::max(sz1.h, sz2.h)));
  }

  void onPaint(PaintEvent& ev) override
  {
    auto theme = SkinTheme::get(this);
    Graphics* g = ev.graphics();
    gfx::Rect bounds = clientBounds();
    ui::Style* style = theme->styles.recentFile();
    ui::Style* styleDetail = theme->styles.recentFileDetail();

    setTextQuiet(m_name.c_str());
    theme->paintWidget(g, this, style, bounds);

    gfx::Size textSize = theme->calcSizeHint(this, style);
    gfx::Rect detailsBounds(bounds.x + textSize.w, bounds.y, bounds.w - textSize.w, bounds.h);
    setTextQuiet(m_path.c_str());
    theme->paintWidget(g, this, styleDetail, detailsBounds);
  }

  void onClick() override
  {
    static_cast<FavoriteListBox*>(parent())->onClick(m_fullpath);
  }

private:
  std::string m_fullpath;
  std::string m_name;
  std::string m_path;

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

void FavoriteListBox::onClick(const std::string& path)
{
  if (!base::is_file(path)) {
    ui::Alert::show(Strings::alerts_favorite_file_doesnt_exist());
    return;
  }

  Command* command = Commands::instance()->byId(CommandId::OpenFile());
  Params params;
  params.set("filename", path.c_str());
  UIContext::instance()->executeCommandFromMenuOrShortcut(command, params);
}

void FavoriteListBox::reload()
{
  while (auto child = lastChild()) {
    removeChild(child);
  }

  auto recent = App::instance()->favoriteFolders();
  for (const auto& fn : recent->favoriteFolders()) {
    addChild(new FavoriteItemSeparator(fn->label()));
    for (const auto& file : fn->listFiles()) {
      if (file.find(m_filter) != std::string::npos)
        addChild(new FavoriteItem(file));
    }
  }

  View* view = View::getView(this);
  if (view)
    view->updateView();
}

void FavoriteListBox::setFilter(const std::string& filter)
{
  m_filter = filter;

  reload();
}

} // namespace app
