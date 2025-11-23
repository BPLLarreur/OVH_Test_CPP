#ifndef ROBOT_H
#define ROBOT_H

#include <string>
#include <vector>
#include <map>

class C_Robot
{
public:
    C_Robot(int id);
    int f_get_id() const;
    void f_rec_word(int index, const std::string &word);
    void f_comm(std::vector<C_Robot> &robots);
    bool f_secret_ok() const;
    std::string f_get_secret() const;
    void f_write_to_file(const std::string &filename) const;

private:
    int id;
    int total_words = -1;
    std::map<int, std::string> words_received;
};

#endif