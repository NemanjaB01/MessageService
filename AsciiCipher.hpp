#ifndef ASCIICIPHER_HPP
#define ASCIICIPHER_HPP

#include <iostream>
#include "Cipher.hpp"
#include <string>
#include "Utils.hpp"


class AsciiCipher : public Cipher
{
  public:
    AsciiCipher(Key key) : Cipher{key}{}
    AsciiCipher(){}
    ~AsciiCipher(){}
    AsciiCipher(const AsciiCipher &AsciiCipher) = delete;
    std::string getCipherTypeString() const override;
    std::string encrypt(const std::string& plain_text) override;
    std::string decrypt(const std::string& cipher_text) override;
};




#endif