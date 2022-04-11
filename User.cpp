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
  std::string string;
  for(auto& it : contacts_)
  {
    if(recipient.compare(it.first->getName()) == 0)
    {
      for(auto &iter : it.first->getContacts())
      {
        if(iter.first->getName().compare(getName()) == 0)
        {
          check = true;
          if(it.second->getCipherTypeString() == "ASCII")
          {
            AsciiCipher ascii;
            string = ascii.encrypt(plain_text);
          }
          else if(it.second->getCipherTypeString() == "CAESAR")
          {
            CaesarCipher caesar;
            string = caesar.encrypt(plain_text);
          }
          else if(it.second->getCipherTypeString() == "NONE")
          {
            NoneCipher none;
            string = none.encrypt(plain_text);
          }
        }
      }
    }
  }
  if(check == false)
  {
    file.close();
    return false;
  }

  file<<"Recipient: "<<recipient<<std::endl;
  file<<"Sender: "<<getName()<<std::endl;
  file<<string <<std::endl;

  file.close();

  std::cout << "\nSending ...\nRecipient: " << recipient << "\nSender: "<< getName() << std::endl;
  std::cout << string;
  std::cout<<std::endl;
  return true;

}


bool User::readMessage(const std::string& filename) const
{
  std::ifstream file;
  file.open(filename);
  std::string line;
  std::string recipient;
  std::string sender;
  std::string delimiter = ":";
  std::string message;
  int end;
  if(!file.is_open())
  {
    return false;
  }
  int counter = 0;
  while(std::getline(file,line))
  {
    if(counter == 0)
    {
      end = line.find(delimiter);
      line.erase(0,end + 2);
      recipient = line;
      counter++;
      if(recipient.compare(getName()) != 0)
      {
        return false;
      }
    }
    else if(counter == 1)
    {
      end = line.find(delimiter);
      line.erase(0,end + 2);
      sender = line;
      counter++;
      bool check;
      for(auto& it : getContacts())
      {
        if(sender.compare(it.first->getName()) == 0)
        {
          check = true;
        }
      }
      if(!check)
      {
        return false;
      }
    }
    else if(counter >= 2)
    {
      message = line;
    }
  }
  std::string new_message;
  for(auto& it : contacts_)
  {
    if(sender.compare(it.first->getName()) == 0)
    {
      if(it.second->getCipherTypeString() == "ASCII")
      {
        AsciiCipher ascii;
        new_message = ascii.decrypt(message);
      }
      else if(it.second->getCipherTypeString() == "CAESAR")
      {
        CaesarCipher caesar;
        new_message = caesar.decrypt(message);
      }
      else if(it.second->getCipherTypeString() == "NONE")
      {
        NoneCipher none;
        new_message = none.decrypt(message);
      }
    }
  }

  IO::printDecryptedMessage(recipient, sender, new_message);

  return true;
}

