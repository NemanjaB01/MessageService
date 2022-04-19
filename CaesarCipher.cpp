#include "CaesarCipher.hpp"

std::string CaesarCipher::getCipherTypeString() const
{
  return "CAESAR";
}


std::string CaesarCipher::encrypt(const std::string& plain_text)
{
  std::string new_string = preparePlainText(plain_text);
  Key key = Cipher::getKey();

  std::string cipher_text;
  int counter = 7;
  for(int n = 0; new_string[n] != '\0';n++)
  {
    int chr = new_string[n];
    int num = (key >> (8 * counter)) & 0xff;
    chr = chr + (num % 26);
    char temp_char = chr;
    if(temp_char < 65 )
    {
      temp_char += 26;
    }
    else if(temp_char > 90)
    {
      temp_char -= 26;
    }
    cipher_text.push_back(temp_char);
    if(counter == 0)
    {
      counter = 7;
      continue;
    }
    counter --;

  }
  return cipher_text;
}


std::string CaesarCipher::decrypt(const std::string& cipher_text)
{
  Key key = Cipher::getKey();
  std::string plain_text;

  int counter = 7;

  for(int n = 0; cipher_text[n] != '\0';n++)
  {
    int chr = cipher_text[n];
    int num = (key >> (8 * counter)) & 0xff;
    chr = chr - (num % 26);
    char temp_char = chr;
    plain_text.push_back(temp_char);
    if(counter == 0)
    {
      counter = 7;
      continue;
    }
    counter --;

  }
  return plain_text;
}