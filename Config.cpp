#include "Config.hpp"


Config::Config(const std::string& filename) : filename_{filename}, modified_{false}
{
  file_.open(filename, std::ios::in);
}


bool Config::isOpen() const
{
  if(file_.is_open())
  {
    return true;
  }
  return false;
}


void Config::setConfigModified()
{
  modified_ = true;
}


void Config::deleteAll()
{
  for(auto& it : users_)
  {
    for(auto& iter : it->getContacts())
    {
      delete(iter.second);
    }
  }
  for(auto &it :users_)
  {
    delete it;
  }
}


bool Config::saveContacts()
{
  std::string line;
  std::string delimiter = ";";
  size_t counter_line;
  size_t row = 0;
  std::string contact_name;
  std::string cipher_type;
  std::string contact_password;
  file_.clear();
  file_.seekg(0,std::ios::beg);
  while(std::getline(file_, line))
  {
    int end;
    counter_line = 0;

    while((end = line.find(delimiter)) != -1)
    {
      if(counter_line == 0)
      {
        line.erase(0,end + 1);
        counter_line++;
        continue;
      }
      else if(counter_line == 1)
      {
        line.erase(0,end + 1);
        counter_line++;
        continue;
      }
      else if(counter_line == 2)
      {
        end = line.find(":");
        contact_name = line.substr(0, end);
        if(contact_name.empty()== true)
        {
          return false;
        }
        line.erase(0,end + 1);

        end = line.find(",");
        cipher_type = line.substr(0, end);
        if(cipher_type.empty() == true)
        {
          return false;
        }
        line.erase(0,end + 1);

        end = line.find(";");
        contact_password = line.substr(0, end);
        if(contact_password.empty() == true)
        {
          return false;
        }
        line.erase(0,end + 1);

        if(contact_password.length() != 16)
        {
          for(auto &it :users_)
          {
            delete it;
          }
          return false;
        }
        if(!(std::all_of(contact_password.begin(),contact_password.end(), ::isxdigit)))
        {
          for(auto &it :users_)
          {
            delete it;
          }
          return false;
        }
        Key key = std::stoul(contact_password, nullptr ,16);
        CipherType type;
        if(cipher_type.compare("ASCII") == 0)
        {
          type = CipherType::ASCII_CIPHER;
        }
        else if(cipher_type.compare("NONE")== 0)
        {
          type = CipherType::NONE_CIPHER;
        }
        else if(cipher_type.compare("CAESAR") == 0)
        {
           type = CipherType::CAESAR_CIPHER;
        }
        else
        {
          for(auto &it :users_)
          {
            delete it;
          }
          return false;
        }

        User* user = users_.at(row);
        User* contact_user = getUser(contact_name);
        user->addContact(contact_user,type,key);

      }
    }
    row++;

  }
  int r = 0;
  int n = 0;
  int counter_contact = 0;
  for(auto& it : users_)
  {
    for(auto& iter : users_)
    {
      if(r != n)
      {
        if(it->getName().compare(iter->getName()) == 0)
        {
          deleteAll();
          return false;
        }
      }
      n++;
    }
    n = 0;
    r++;
    bool check = false;

    for(auto& ite : it->getContacts())
    {
      counter_contact = 0;
      if(it->getName().compare(ite.first->getName()) == 0)
      {
        deleteAll();
        return false;
      }
      for(auto& iterator : ite.first->getContacts())
      {
        if(iterator.first->getName().compare(it->getName()) == 0)
        {
          check = true;
        }
      }
      for(auto& contact_ite : it ->getContacts())
      {
        if(ite.first->getName().compare(contact_ite.first->getName()) == 0)
        {
          counter_contact++;
        }
      }
      if(!check || (counter_contact > 1))
      {
        deleteAll();
        return false;
      }
    }
  }

  for(auto &first : users_)
  {
    for(auto& iter : first->getContacts())
    {
      for(auto& second : users_)
      {
        if(iter.first->getName().compare(second->getName()) == 0)
        {
          for(auto& it : second->getContacts())
          {
            if((it.first->getName().compare(first->getName())== 0))
            {
              if((it.second->getCipherTypeString().compare(iter.second->getCipherTypeString()) != 0) || ((it.second->getKey()) != (iter.second->getKey())))
              {
                deleteAll();
                return false;
              }
            }
          }
        }
      }
    }
  }

  return true;
}


bool Config::parseFile()
{
  std::string line;

  while(std::getline(file_,line))
  {
    std::string delimiter = ";";
    size_t end = 0;
    std::string parse_string;
    size_t counter = 0;
    std::string user_name;
    std::string user_passweord;
    while((end = line.find(delimiter)) != std::string::npos)
    {
      parse_string = line.substr(0, end);
      if(parse_string.empty() == true)
      {
        return false;
      }

      if(counter == 0)
      {
        for(auto& c : parse_string)
        {
          if((c < 65 || c > 90)&&(c < 97 || c > 122) && (c < 48 || c > 57))
          {
            for(auto &it :users_)
            {
              delete it;
            }
            return false;
          }
        } 
        user_name = parse_string;
        line.erase(0, end + delimiter.length());
        counter++;
        continue;
      }
      else if(counter == 1)
      {
        for(auto& c : parse_string)
        {
          if((c < 65 || c > 90)&&(c < 97 || c > 122) && (c < 48 || c > 57))
          {
            for(auto &it :users_)
            {
              delete it;
            }
            return false;
          }
        }
        user_passweord = parse_string;
        if(user_passweord.empty() == true)
        {
          return false;
        }
        line.erase(0, end + delimiter.length());
      }
      User* user = new User(user_name,user_passweord);
      users_.push_back(user);
      counter = 0;
      break;
    }
  }

  if(!saveContacts())
  {
    return false;
  }

  return true;
}

bool Config::containsUser(const std::string& name) const
{
  for(auto& it : users_)
  {
    if(name.compare(it->getName())== 0)
    {
      return true;
    }
  }

  return false;
}

User* Config::getUser(const std::string& name) const
{
  for(auto& it : users_)
  {
    if(name.compare(it->getName())== 0)
    {
      return it;
    }
  }

  return nullptr;

}


User* Config::registerUser(const std::string& name, const std::string& password)
{
  User* user_pointer = new  User(name, password);
  users_.push_back(user_pointer);
  setConfigModified();

  return user_pointer;
}


User* Config::loginUser(const std::string& name, const std::string& password) const
{
  for(auto& it : users_)
  {
    if(name.compare(it->getName())== 0)
    {
      if(it->verifyPassword(password))
      {
        return it;
      }
    }
  }

  return nullptr;
}

bool Config::updateConfigFile()
{
  std::ofstream file;
  file.open(filename_);
  if(modified_ == true)
  {
    for(auto &it : users_)
    {
      file<<it->getName()<<";"<<it->getPassword()<<";";
      auto contact = it->getContacts();
      for(auto &iter : contact)
      {
        file<<iter.first->getName()<<":";
        file<<iter.second->getCipherTypeString()<<",";
        std::stringstream stream;
        stream<<std::hex<<iter.second->getKey();
        std::string result = stream.str();
        if(result.length() == 16)
        {
          file<<result<<";";
        }
        else
        {
          file<<"0"<<result<<";";
        }
      }
      file<<std::endl;
    }
    file.close();

    modified_ = false;
    deleteAll();
    return true;
  }
  deleteAll();

  return true;
}