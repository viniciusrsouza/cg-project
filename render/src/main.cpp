// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <window/buffered_pane.h>
#include <iostream>

#include <mathlib.h>
#include <filelib.h>

/**
 * height -> 0xff
 * line -> x
 *
 * x * height = line * 0xff
 * x = line * 0xff / height
 *
 */

class MyPane : public BaseBufferedPane
{
public:
  MyPane(wxFrame *parent) : BaseBufferedPane(parent) {}
  void Render(uint8_t *buffer, int size) override
  {
    std::cout << "Render" << std::endl;
    for (int i = 0; i < size; i += 3)
    {
      int line = (i / 3) / GetSize().GetWidth();
      int column = (i / 3) - line * GetSize().GetWidth();

      uint8_t b_shade = 0xff * line / this->GetSize().GetHeight();
      uint8_t g_shade = 0xff * column / this->GetSize().GetWidth();
      uint8_t r_shade = 0xff * (this->GetSize().GetHeight() - line) / this->GetSize().GetHeight();
      buffer[i + 0] = r_shade;
      buffer[i + 1] = g_shade;
      buffer[i + 2] = b_shade;
    }
  }

  void KeyDown(int key) override
  {
    switch (key)
    {
    case (int)'R':
    {
      Reload();
      break;
    }
    default:
      break;
    }
  }

  void Reload()
  {
    File *file = new File("assets/calice2.byu");
    file->Load();
    mat3 m(1.0f);
    mat3 m2(m);
    mat3 m3(0.0f, 1.0f, 2.0f,
            3.0f, 8.0f, 5.0f,
            6.0f, 7.0f, 8.0f);

    std::cout << m << std::endl;
    std::cout << m2 << std::endl;
    std::cout << m3 << std::endl;
    std::cout << m2(1, 1) << std::endl;
    std::cout << "det " << m3.determinant() << std::endl;
    std::cout << "inv " << std::endl
              << m3.inverse() << std::endl;
  }
};

class MyApp : public wxApp
{
  bool OnInit();

  wxFrame *frame;
  MyPane *drawPane;

public:
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
  wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
  frame = new wxFrame((wxFrame *)NULL, -1, wxT("Hello wxDC"), wxPoint(50, 50), wxSize(800, 600));

  drawPane = new MyPane((wxFrame *)frame);
  sizer->Add(drawPane, 1, wxEXPAND);

  frame->SetSizer(sizer);
  frame->SetAutoLayout(true);

  frame->Show();

  return true;
}

BEGIN_EVENT_TABLE(BaseBufferedPane, wxPanel)
// some useful events
/*
 EVT_MOTION(BaseBufferedPane::mouseMoved)
 EVT_LEFT_DOWN(BaseBufferedPane::mouseDown)
 EVT_LEFT_UP(BaseBufferedPane::mouseReleased)
 EVT_RIGHT_DOWN(BaseBufferedPane::rightClick)
 EVT_LEAVE_WINDOW(BaseBufferedPane::mouseLeftWindow)
 EVT_KEY_DOWN(BaseBufferedPane::keyPressed)
 EVT_KEY_UP(BaseBufferedPane::keyReleased)
 EVT_MOUSEWHEEL(BaseBufferedPane::mouseWheelMoved)
 */

// catch paint events
EVT_PAINT(MyPane::PaintEvent)
EVT_SIZE(MyPane::SizeEvent)
EVT_KEY_DOWN(MyPane::KeyDownEvent)

END_EVENT_TABLE()