#include <fstream>
#include <algorithm>
#include "robot.h"
#include <map>
#include <iostream>

using namespace std;

C_Robot::C_Robot(int id) : id(id) {}

int C_Robot::f_get_id() const
{
    return id;
}

//==================================f_rec_word()============================================
// desc: Receive a word from the scheduler and bind it to a robot                          =
// input : integer index to identify the word                                              =
//         const string word to save                                                       =
// ouput : void                                                                            =
//==========================================================================================
void C_Robot::f_rec_word(int index, const string &word)
{
    // store by index; if already there keep the first received
    if (words_received.find(index) == words_received.end())
    {
        words_received[index] = word;
    }
}

//====================================f_secret_ok()=========================================
// desc: Communication between all the robots, the robot get the word he doesn't have yet  =
//       avoiding duplicates                                                               =
// input : vector robot containing initialized robots                                      =
// ouput : void                                                                            =
//==========================================================================================

void C_Robot::f_comm(vector<C_Robot> &robots)
{
    for (auto &otherRobot : robots) // through all robots in vector
    {

        if (otherRobot.id == this->id) // if itself, next robot
            continue;

        for (const auto &i : otherRobot.words_received) // for each word known by other robot in map words_received
        {
            int index = i.first;
            const std::string &w = i.second;
            if (words_received.find(index) == words_received.end()) // if index not in robot's map, add it
                words_received[index] = w;
        }

        cout << "my secret is now : ";
        for (const auto &i : words_received)
        {
            cout << "[" << i.first << "] '" << i.second << "' ";
        }
        cout << endl;
    }

    if (total_words == -1)
    {
        for (const auto &i : words_received)
        {
            if (i.second.find('.') != std::string::npos)
            {
                total_words = i.first + 1;
                break;
            }
        }
    }
}

//====================================f_secret_ok()=========================================
// desc: Check if the secret sentence is OK, if we have all words and last word ends       =
//       with '.'                                                                          =
// input :                                                                                 =
// ouput :                                                                                 =
//==========================================================================================

bool C_Robot::f_secret_ok() const
{
    // Secret is OK if we have all words and last word ends with '.'
    if (total_words <= 0) // if undefined, cannot be complete
        return false;
    if ((int)words_received.size() != total_words) // if we don't have all words, cannot be complete
        return false;
    auto i = words_received.find(total_words - 1);
    if (i == words_received.end()) // if word at index total_words-1 (last word of words_received) not exists, cannot be complete
        return false;
    return i->second.find('.') != std::string::npos; // if last word contains '.', secret is OK
}

//================================f_get_secret()============================================
// desc: Build and return the secret string by concat words stored in words_received       =
//       using their index and separated by spaces                                         =
// input :                                                                                 =
// ouput : string secret sentence                                                          =
//==========================================================================================

string C_Robot::f_get_secret() const
{
    std::string secret;
    for (int i = 0; i < total_words; ++i)
    {
        auto j = words_received.find(i);
        if (j != words_received.end()) // for each index see if word exists
        {
            secret += j->second; // if exists, append word to secret
            if (i != total_words - 1)
                secret += " "; // append space if not last word
        }
    }
    return secret;
}

//================================f_write_to_file()=========================================
// desc: Write all the words to a file                                                     =
// input : string name of output file                                                      =
// ouput : void                                                                            =
//==========================================================================================

void C_Robot::f_write_to_file(const std::string &filename) const
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        std::string secret = f_get_secret();
        file << secret << std::endl;
        file.close();
    }
}
