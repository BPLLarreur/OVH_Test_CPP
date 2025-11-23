// SecretManager.cpp
#include "scheduler.h"
#include <algorithm>
#include <random>
#include <ctime>
#include <iostream>

using namespace std;

//===============================C_Scheduler()==============================================
// desc: Initialize the scheduler with the secret string and while spaces in string,       =
//       extract word between start and end + add it to vector SecretsWords to be rand sent=
// input: string                                                                           =
//==========================================================================================

C_Scheduler::C_Scheduler(const std::string &secret)
{
    size_t start = 0;
    size_t end = secret.find(' ');

    while (end != string::npos)
    {
        SecretsWords.push_back(secret.substr(start, end - start));
        start = end + 1;               // start pos updated after next ' '
        end = secret.find(' ', start); // end update to find next ' '
    }
    SecretsWords.push_back(secret.substr(start));
    // in the end : ["Hidden", "beneath", "the", "old", "oak", "tree,", "golden", "coins", "patiently", "await", "discovery."]
}

//===========================f_send_words_to_robots()=======================================
// desc: Send randomly the secret's words to the robots                                    =
// input : vector list of robots                                                           =
// ouput : void                                                                            =
//==========================================================================================
void C_Scheduler::f_send_words_to_robots(std::vector<C_Robot> &robots)
{
    std::srand(std::time(0)); // init random generator

    int total = static_cast<int>(SecretsWords.size()); // total words count in secret sentence
    for (auto &r : robots)
        r.f_set_total_words(total); // inform each robot of total words count

    for (int i = 0; i < (int)SecretsWords.size(); ++i) // for each word in secret, send it to a random robot
    {
        const auto &word = SecretsWords[i];
        int robotIndex = std::rand() % robots.size(); // choosen randomly
        robots[robotIndex].f_rec_word(i, word);
        cout << "robot " << robotIndex << " received [" << i << "] '" << word << "'" << endl;
    }
}

//==============================f_rebuild_secret()==========================================
// desc: Schedule the reconstruction of the secret                                         =
// input : vector list of robots                                                           =
//       : string output file name                                                         =
// ouput : void                                                                            =
//==========================================================================================
void C_Scheduler::f_rebuild_secret(std::vector<C_Robot> &robots, const std::string &fileName)
{
    bool secretComplete = false;
    while (!secretComplete) // repeat comm process until one robot has complete secret
    {
        for (auto &robot : robots) // each robot call its comm function
        {
            robot.f_comm(robots);
            if (robot.f_secret_ok()) // after each comm check if secrete complete
            {
                // Only first robot that detect the complete secret writes it
                robot.f_write_to_file(fileName);
                secretComplete = true;
                break;
            }
        }
    }
}
