#ifndef CIPHER_HPP
#define CIPHER_HPP

#include <string>
#include <iostream>


typedef uint64_t Key;

enum class CipherType{INVALID, NONE_CIPHER, ASCII_CIPHER, CAESAR_CIPHER };

class Cipher
{
  private:
    Key key_;

  public:
    Cipher(Key key) : key_{key} {}
    Cipher(const std::string& plain_text);
    Cipher() = default;
    Key getKey();
    std::string preparePlainText(const std::string& plain_text) const;
    Cipher(const Cipher &Cipher) = delete;
    static CipherType getCipherType(const std::string& type);
    virtual std::string getCipherTypeString() const = 0;
    virtual std::string encrypt(const std::string& plain_text) = 0;
    virtual std::string decrypt(const std::string& cipher_text) = 0;
    virtual ~Cipher(){}
};

#endif