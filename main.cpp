#include "robot.h"
#include "scheduler.h"
#include <iostream>

using namespace std;

int main()
{
    cout << "OVH Test C++ - Secret Reconstruction Simulation Starting" << endl;

    const string secret = "Hidden beneath the old oak tree, golden coins patiently await discovery.";
    cout << secret << endl;
    const string fileName = "secret.txt";

    vector<C_Robot> robots;

    // create 6 robots
    for (int i = 0; i < 6; ++i)
    {
        robots.push_back(C_Robot(i));
    }

    // create and init scheduler with secret
    C_Scheduler scheduler(secret);

    // send randomly words to robots
    scheduler.f_send_words_to_robots(robots);

    // let the robots communicate to rebuild the secret sentence
    scheduler.f_rebuild_secret(robots, fileName);

    cout << "secret found and written to file '" << fileName << "'." << endl;

    return 0;
}