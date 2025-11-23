#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "robot.h"
#include <vector>
#include <string>

class C_Scheduler
{
public:
    C_Scheduler(const std::string &secret);
    void f_send_words_to_robots(std::vector<C_Robot> &robots);
    void f_rebuild_secret(std::vector<C_Robot> &robots, const std::string &fileName);

private:
    std::vector<std::string> SecretsWords;
};

#endif