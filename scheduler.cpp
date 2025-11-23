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
    if (robots.empty())
    {
        return;
    }

    std::srand(std::time(0)); // init random generator
    std::vector<int> remaining;
    remaining.reserve(SecretsWords.size()); // Build list of remaining words

    for (int i = 0; i < (int)SecretsWords.size(); ++i)
    {
        remaining.push_back(i);
    }

    while (!remaining.empty()) // Loop over robots and assign random word
    {
        for (int j = 0; j < (int)robots.size() && !remaining.empty(); ++j)
        {
            int pos = std::rand() % remaining.size();
            int wordIndex = remaining[pos];
            const auto &word = SecretsWords[wordIndex];

            robots[j].f_rec_word(wordIndex, word);
            cout << "Init robot " << j << " received [" << wordIndex << "] '" << word << "'" << endl;

            // remove the assigned word from the remaining pool
            remaining.erase(remaining.begin() + pos);
        }
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
