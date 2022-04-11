#ifndef CAESARCIPHER_HPP
#define CAESARCIPHER_HPP

#include <iostream>
#include "Cipher.hpp"
#include <string>
#include "Utils.hpp"

class CaesarCipher : public Cipher
{
  public:
    CaesarCipher(Key key) : Cipher{key}{}
    CaesarCipher(){}
    ~CaesarCipher(){}
    CaesarCipher(const CaesarCipher &Cipher) = delete;
    std::string getCipherTypeString() const override;
    std::string encrypt(const std::string& plain_text) override;
    std::string decrypt(const std::string& cipher_text) override;

};


#endif