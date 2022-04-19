#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <string>
#include <map>
#include "Cipher.hpp"
#include "Utils.hpp"
#include "AsciiCipher.hpp"
#include "NoneCipher.hpp"
#include "CaesarCipher.hpp"
#include <fstream>
#include "IO.hpp"
#include "Config.hpp"
#include "Cipher.hpp"


class User
{
  private:
    std::string name_;
    std::string password_;
    std::map<User*, Cipher* ,bool(*)(User*, User*)> contacts_;
  public:
    User() = default;
    User(const std::string& name, const std::string& password)
    : name_{name}, password_{password}, contacts_{Utils::sortContactsAlphabetically}{};
    User(const User &User) = delete;
    std::string getName() const;
    std::string getPassword() const;
    const auto& getContacts() const {return contacts_;}
    bool verifyPassword(const std::string& password) const;
    bool hasContact(const std::string& name) const;
    void addContact(User* contact, CipherType type, Key key);
    bool sendMessage(const std::string& recipient, const std::string& filename, const std::string& plain_text) const;
    bool readMessage(const std::string& filename) const;
    ~User(){}

};


#endif