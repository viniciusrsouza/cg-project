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
  InitBuffers();
  timer = new Timer();
}

void BaseBufferedPane::InitBuffers()
{
  uint8_t *oldBack = backBuffer;
  uint8_t *oldFront = frontBuffer;

  backBuffer = (uint8_t *)malloc(GetBufferSize());
  frontBuffer = (uint8_t *)malloc(GetBufferSize());
  blankBuffer = (uint8_t *)malloc(GetBufferSize());
  memset(blankBuffer, 0, GetBufferSize());

  if (oldBack != NULL)
    free(oldBack);
  if (oldFront != NULL)
    free(oldFront);
}

/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */

void BaseBufferedPane::PaintEvent(wxPaintEvent &evt)
{
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
    Render(backBuffer, GetBufferSize());
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
void BaseBufferedPane::Render(uint8_t *buffer, int size)
{
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