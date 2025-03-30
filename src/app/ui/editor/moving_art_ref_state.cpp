#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#include "app/ui/editor/moving_art_ref_state.h"

#include "app/ui/editor/editor.h"
#include "app/ui/editor/editor_hit.h"
#include "ui/message.h"

#include <algorithm>
#include <cmath>

namespace app {

using namespace ui;

MovingArtRefState::MovingArtRefState(Editor* editor,
                                     ui::MouseMessage* msg,
                                     const EditorHit& hit,
                                     // TODO: Check this later
                                     doc::ArtRef* artRef)
  : m_selected(artRef)
{
  m_mouseStart = editor->screenToEditor(msg->position());
  editor->captureMouse();
}

bool MovingArtRefState::onMouseUp(Editor* editor, MouseMessage* msg)
{
  editor->backToPreviousState();
  editor->releaseMouse();
  return true;
}

bool MovingArtRefState::onMouseMove(Editor* editor, MouseMessage* msg)
{
  gfx::Point newCursorPos = editor->screenToEditor(msg->position());
  gfx::Point delta = newCursorPos - m_mouseStart;
  gfx::Rect bounds = m_selected->bounds();

  bounds.x += delta.x;
  bounds.y += delta.y;

  m_selected->setBounds(bounds);

  // Redraw the editor.
  editor->invalidate();

  // Use StandbyState implementation
  return StandbyState::onMouseMove(editor, msg);
}

bool MovingArtRefState::onSetCursor(Editor* editor, const gfx::Point& mouseScreenPos)
{
  editor->showMouseCursor(kArrowCursor);
  return true;
}

} // namespace app
