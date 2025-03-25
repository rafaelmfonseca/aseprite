#ifndef APP_UI_FAVORITE_LISTBOX_H_INCLUDED
#define APP_UI_FAVORITE_LISTBOX_H_INCLUDED
#pragma once

#include "base/paths.h"
#include "ui/listbox.h"
#include "ui/view.h"

namespace app {

class FavoriteItem;

class FavoriteListBox : public ui::ListBox,
                        public ui::ViewableWidget {
  friend class FavoriteItem;

public:
  FavoriteListBox();

  void updateRecentListFromUIItems();

protected:
  // ui::ViewableWidget impl
  virtual void onScrollRegion(ui::ScrollRegionEvent& ev);

  virtual void onRebuildList() = 0;
  virtual void onClick(const std::string& path) = 0;
  virtual void onUpdateRecentListFromUIItems(const base::paths& favoritePaths) = 0;

private:
  void rebuildList();
};

} // namespace app

#endif