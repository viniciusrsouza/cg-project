#include <window/buffered_pane.h>
#include <utils/timer.h>
#include <cstdlib>
#include <iostream>

// some useful events
/*
 void BaseBufferedPane::mouseMoved(wxMouseEvent& event) {}
 void BaseBufferedPane::mouseDown(wxMouseEvent& event) {}
 void BaseBufferedPane::mouseWheelMoved(wxMouseEvent& event) {}
 void BaseBufferedPane::mouseReleased(wxMouseEvent& event) {}
 void BaseBufferedPane::rightClick(wxMouseEvent& event) {}
 void BaseBufferedPane::mouseLeftWindow(wxMouseEvent& event) {}
 void BaseBufferedPane::keyPressed(wxKeyEvent& event) {}
 void BaseBufferedPane::keyReleased(wxKeyEvent& event) {}
 */

BaseBufferedPane::BaseBufferedPane(wxFrame *parent) : wxPanel(parent)
{
  backBuffer = nullptr;
  frontBuffer = nullptr;
  blankBuffer = nullptr;
  InitBuffers();
  timer = new Timer();
}

void BaseBufferedPane::InitBuffers()
{
  std::cout << "InitBuffers - before" << std::endl;
  if (backBuffer != nullptr)
    free(backBuffer);
  if (frontBuffer != nullptr)
    free(frontBuffer);
  if (blankBuffer != nullptr)
    free(blankBuffer);
  std::cout << "InitBuffers - after" << std::endl;

  backBuffer = (uint8_t *)malloc(GetBufferSize());
  frontBuffer = (uint8_t *)malloc(GetBufferSize());
  blankBuffer = (uint8_t *)malloc(GetBufferSize());
  memset(blankBuffer, 0, GetBufferSize());
}

/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */

void BaseBufferedPane::PaintEvent(wxPaintEvent &evt)
{
  std::cout << "PaintEvent" << std::endl;
  wxPaintDC dc(this);
  PerformPaint(dc);
}

void BaseBufferedPane::DispatchPaint()
{
  resizing = false;
  wxThreadEvent *evt = new wxThreadEvent();
  evt->SetEventType(wxEVT_PAINT);
  wxQueueEvent(this, evt);
}

/**
 * @brief Called by the system of by wxWidgets when the panel size has changed.
 * Reallocates buffers.
 *
 * @param evt
 */
void BaseBufferedPane::SizeEvent(wxSizeEvent &evt)
{
  resizing = true;
  timer->Stop();
  InitBuffers();

  // delays paint event after resize to
  // avoid running demanding render function.
  timer->SetTimeout([this]()
                    { DispatchPaint(); },
                    500);
}

void BaseBufferedPane::KeyDownEvent(wxKeyEvent &evt)
{
  switch (evt.GetKeyCode())
  {
  case WXK_ESCAPE:
    wxTheApp->ExitMainLoop();
    break;
  case (int)'R':
    PaintNow();
    break;
  default:
    break;
  }
  KeyDown(evt.GetKeyCode());
}

void BaseBufferedPane::KeyDown(int key)
{
  // override
}

/*
 * Can be called to force a repaint of the window.
 */
void BaseBufferedPane::PaintNow()
{
  wxClientDC dc(this);
  PerformPaint(dc);
}

void BaseBufferedPane::PerformPaint(wxDC &dc)
{
  if (!resizing)
  {
    auto size = GetSize();
    Render(backBuffer, size.GetWidth(), size.GetHeight());
    SwapBuffers();
  }

  uint8_t **buff = resizing ? &blankBuffer : &frontBuffer;
  wxImage bitmap = wxImage(GetSize(), (unsigned char *)*buff, true);

  dc.DrawBitmap(bitmap, 0, 0);
}

/*
 * Debug implementation of virtual function. Derived class
 * should override this method to draw the contents of the window.
 */
void BaseBufferedPane::Render(uint8_t *buffer, int w, int h)
{
  int size = w * h * 3;
  for (int i = 0; i < size; i += 3)
  {
    uint8_t color = 0xff * i / size;
    buffer[i + 0] = 0x00;
    buffer[i + 1] = 0x00;
    buffer[i + 2] = 0xff;
  }
}

void BaseBufferedPane::SwapBuffers()
{
  uint8_t *tmp = frontBuffer;
  frontBuffer = backBuffer;
  backBuffer = tmp;
}

int BaseBufferedPane::GetBufferSize()
{
  return GetSize().GetWidth() * GetSize().GetHeight() * 3;
}