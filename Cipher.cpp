#include "Cipher.hpp"

Key Cipher::getKey()
{
  return key_;
}

std::string Cipher::preparePlainText(const std::string& plain_text) const
{
  std::string new_string;
  for(int i = 0;plain_text[i] != '\0';i++)
  {
    char temp = plain_text[i];
    if(temp > (int)64 && temp < (int)91)
    {
      new_string.push_back(temp);
    }
    else if(temp > (int)96 && temp < (int)123)
    {
      temp -= 32;
      new_string.push_back(temp);
    }
  }
  return new_string;
}

CipherType Cipher::getCipherType(const std::string& type)
{
  int check;
  check = type.compare("NONE");
  if (check == 0)
  {
    return CipherType::NONE_CIPHER;
  }
  check = type.compare("ASCII");
  if (check == 0)
  {
    return CipherType::ASCII_CIPHER;
  }
  check = type.compare("CAESAR");
  if (check == 0)
  {
    return CipherType::CAESAR_CIPHER;
  }
  else
  {
    return CipherType::INVALID;
  }
}