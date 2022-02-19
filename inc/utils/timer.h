#pragma once

#include <thread>

class Timer
{
public:
  template <typename Function>
  void SetTimeout(Function function, int delay)
  {
    clear = false;
    std::thread t([=]()
                  {
    if(clear || id != std::this_thread::get_id()) return;
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    if(clear || id != std::this_thread::get_id()) return;
    function(); });
    id = t.get_id();
    t.detach();
  }

  template <typename Function>
  void SetInterval(Function function, int interval)
  {
    clear = false;
    std::thread t([=]()
                  {
        while(true) {
            if(clear || id != std::this_thread::get_id()) return;
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            if(clear || id != std::this_thread::get_id()) return;
            function();
        } });
    id = t.get_id();
    t.detach();
  }

  void Stop()
  {
    clear = true;
  }

private:
  bool clear = false;
  std::thread::id id;
};
