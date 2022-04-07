#include "User.hpp"

std::string User::getName() const
{
  return name_;
}

std::string User::getPassword() const
{
  return password_;
}

bool User::verifyPassword(const std::string& password) const
{
  if(password_.compare(password) == 0)
  {
    return true;
  }
  return false;
}

bool User::hasContact(const std::string& name) const
{

  for(auto& iterator : contacts_)
  {
    if(name.compare(iterator.first->name_) == 0)
    {
      return true;
    }
  }
  return false;
}


void User::addContact(User* contact, CipherType type, Key key)
{
  Cipher* pointer_base_class;
  if(type == CipherType::ASCII_CIPHER)
  {
    pointer_base_class = new AsciiCipher(key);;
    contacts_.insert( std::pair<User*,Cipher*>(contact, pointer_base_class) );
  }
  else if(type == CipherType::CAESAR_CIPHER)
  {
    pointer_base_class = new CaesarCipher(key);
    contacts_.insert( std::pair<User*,Cipher*>(contact, pointer_base_class) );
  }
  else if(type == CipherType::NONE_CIPHER)
  {
    pointer_base_class = new NoneCipher(key);
    contacts_.insert( std::pair<User*,Cipher*>(contact, pointer_base_class) );
  }

}


bool User::sendMessage(const std::string& recipient, const std::string& filename, const std::string& plain_text) const
{
  std::ofstream file;
  file.open(filename);
   CipherType type;
  if(!file.is_open())
  {
    return false;
  }
  bool check = false;
  for(auto& it : contacts_)
  {
    if(recipient.compare(it.first->getName()) == 0)
    {
      for(auto &iter : it.first->getContacts())
      {
        if(iter.first->getName().compare(getName()) == 0)
        {
         // type = iter.second->getCipherType();
        }
      }
    }
  }
  if(check == false)
  {
    file.close();
    return false;
  }

  file.close();
  IO::printEncryptedMessage(plain_text);
  return true;

}


bool User::readMessage(const std::string& filename) const
{
  /*std::fstream file;
  file.open("filename", std::ios::out);
  if(!file.is_open())
  {
    return false;
  }*/

  return true;
}

