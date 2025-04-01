#ifndef APP_COMMANDS_CMD_ADD_ART_REF_H_INCLUDED
#define APP_COMMANDS_CMD_ADD_ART_REF_H_INCLUDED
#pragma once

#include "app/commands/command.h"
#include "app/commands/new_params.h"
#include "gfx/point.h"

namespace app {
class Editor;
class Site;

class AddArtRefCommand : public Command {
public:
  AddArtRefCommand();

  void executeOnMousePos(Context* context,
                         Editor* editor,
                         const gfx::Point& mousePos);

protected:
  bool onEnabled(Context* ctx) override;
  void onExecute(Context* ctx) override;
};

} // namespace app

#endif // APP_COMMANDS_CMD_ADD_ART_REF_H_INCLUDED