#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "User.hpp"
#include <algorithm>
#include "Cipher.hpp"
#include <iomanip>

class Config
{
  private:
    std::fstream file_;
    std::string filename_;
    bool modified_;
    std::vector <User*> users_;

  public:
    Config(const std::string& filename);
    Config(const Config &Config) = delete;
    ~Config(){}
    bool isOpen() const;
    void setConfigModified();
    bool saveContacts();
    bool parseFile();
    bool containsUser(const std::string& name) const;
    User* getUser(const std::string& name) const;
    User* registerUser(const std::string& name, const std::string& password);
    User* loginUser(const std::string& name, const std::string& password) const;
    bool updateConfigFile();




};

#endif