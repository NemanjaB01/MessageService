#include "NoneCipher.hpp"

std::string NoneCipher::getCipherTypeString() const
{
  return "NONE";
}

std::string NoneCipher::encrypt(const std::string& plain_text)
{
  std::string newstring = preparePlainText(plain_text);
  return newstring;
}

std::string NoneCipher::decrypt(const std::string& cipher_text)
{
  return cipher_text;
}