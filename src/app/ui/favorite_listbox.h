#ifndef APP_UI_FAVORITE_LISTBOX_H_INCLUDED
#define APP_UI_FAVORITE_LISTBOX_H_INCLUDED
#pragma once

#include "base/paths.h"
#include "ui/listbox.h"
#include "ui/view.h"

namespace app {

class FavoriteItem;
class FavoriteItemSeparator;

class FavoriteListBox : public ui::ListBox {
  friend class FavoriteItem;
  friend class FavoriteItemSeparator;

public:
  FavoriteListBox();
  
  void setFilter(const std::string& filter);

protected:
  void onClick(const std::string& path);

private:
  void reload();

  std::string m_filter;
};

} // namespace app

#endif