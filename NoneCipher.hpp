#ifndef NONECIPHER_HPP
#define NONECIPHER_HPP

#include <string>
#include <iostream>
#include "Cipher.hpp"


class NoneCipher : public Cipher
{
  public:
    NoneCipher(Key key) : Cipher{key}{}
    NoneCipher(){}
    ~NoneCipher(){}
    NoneCipher(const NoneCipher &NoneCipher) = delete;
    std::string getCipherTypeString() const override;
    std::string encrypt(const std::string& plain_text) override;
    std::string decrypt(const std::string& cipher_text) override;
};



#endif