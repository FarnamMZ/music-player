#pragma once
#include <string>

class QueueUI
{
public:
  void run();
private:
  void drawQueuePage();
  void clearQueue();
  void processCommand(const std::string &command, bool &running);
};
