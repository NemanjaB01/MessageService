#include "AsciiCipher.hpp"

std::string AsciiCipher::getCipherTypeString() const
{
  return "ASCII";
}

std::string AsciiCipher::encrypt(const std::string& plain_text)
{
  std::string new_string = preparePlainText(plain_text);
  std::string clipertext;
  Key key = Cipher::getKey();
  key %= 10;

  for(auto c : new_string)
  {
    c -= key;
    int i = c;
    clipertext += std::to_string(i);
    clipertext += ' ';
  }
  clipertext.pop_back();

  return clipertext;
}

std::string AsciiCipher::decrypt(const std::string& cipher_text)
{
  std::string text;
  std::string new_string;
  new_string.assign(cipher_text);
  Key key = Cipher::getKey();
  key %= 10;
  char result = 0;
  bool return_type = true;

  while(true)
  {
    return_type = Utils::decimalStringToInt(new_string,result);
    new_string.erase(0,3);
    if(result == ' ')
    {
      continue;
    }
    else if(result < 65 )
    {
      result += 26;
    }
    else if(result > 90)
    {
      result -= 26;
    }
    text += result;
    if(new_string.length()== 0)
    {
      break;
    }
  }

  return text;

}