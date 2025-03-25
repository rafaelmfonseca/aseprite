#ifndef APP_UI_FAVORITE_LISTBOX_H_INCLUDED
#define APP_UI_FAVORITE_LISTBOX_H_INCLUDED
#pragma once

#include "base/paths.h"
#include "ui/listbox.h"
#include "ui/view.h"

namespace app {

class FavoriteItem;

class FavoriteListBox : public ui::ListBox {
  friend class FavoriteItem;

public:
  FavoriteListBox();

  void reload();
};

} // namespace app

#endif