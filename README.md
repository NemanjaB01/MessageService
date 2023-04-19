# Assignment 1 - messaging service

In Assignment 1 (A1) of the construction exercise (KU), a program is to be written with which messages - similar to a messaging service - can be exchanged between users in encrypted form. Two simple classic methods (such as a version of the Caesar cipher) are to be implemented as encryption algorithms.

---

## Learning goals

- Understand classes
   - Attributes, methods
   - Constructor, copy constructor, destructor
- heredity
   - virtual methods
   - abstract classes
- Strings & Streams (will be presented in the VO on March 31)
   - `std::string`
   - Files
- Data structures from the Standard Template Library
   - e.g. `std::vector` or `std::map`

---

## specification

- official release: 3/24/2022 after the VO stream
- To be submitted by (soft deadline): April 19, 2022 at 11:59 p.m. (valid time in Austria)
- Extension period for a repair until (hard deadline): April 23, 2022 at 11:59 p.m. (valid time in Austria)
- The framework consisting of `main.cpp`, `IO.hpp`, `IO.cpp` and `Utils.hpp` and `Utils.cpp` may **NOT** be modified.
- Only C++ standard libraries may be used
- A1 is **not** group work. Each student receives their own Gitlab repository from the course team and the assignment is **independent**
   edit. Please read our [Guidelines on Plagiarism](https://tc.tugraz.at/main/mod/page/view.php?id=256924#Plagiarism) carefully!
- The submission must be made on a separate git branch called `submission`. That means before the grace period expires
   your own solution must have been sent to the `submission` branch of your own Gitlab repository for A1 using `git push`.

---

## Evaluation

**Caution: For a positive assessment in the KU, at least half of the public test cases must be passed.**

The assignment is evaluated as described in the [TeachCenter](https://tc.tugraz.at/main/mod/page/view.php?id=138898), but with two exceptions:

1. With the A1 **only the functionality is evaluated**, but not the coding standard.
2. There will be **no submission talks** for the A1.

The assessment scheme for the construction exercise can also be found in the [TeachCenter](https://tc.tugraz.at/main/mod/page/view.php?id=256924), in particular the rules for [plagiarism]( https://tc.tugraz.at/main/mod/page/view.php?id=256924#Plagiarism).

---

## Description

### Overview

In A1, a program is to be implemented in which messages - similar to a messaging service - are exchanged between users in encrypted form.

The program is based on a configuration file that defines who is registered for this messaging service and can therefore also use it. This configuration file also records which other people (contacts) a user can exchange messages with.

In order for a user to be able to use the messaging service, he must log in at the beginning of the program. If this was successful, it is possible for the user to send messages to their own contacts or to read messages that have already been received.

It is important here that all sent messages are stored in encrypted form in text files so that it is not possible for other users to simply read the content of the messages from the text files. Conversely, this also means that received messages must first be decrypted so that they can be read.

Note: Normally you would send messages to and receive messages from a server. To simplify this in A1, sent messages are only saved in text files.
---

### classes

#### cipher

In order to be able to send encrypted messages, we need an encryption algorithm. In this assignment, encryption algorithms are represented by classes. A class called `Cipher` should serve as the base class for all encryption algorithms. The respective encryption algorithms are to be implemented in the classes derived from it. A detailed description of the classes can be found under [description/Cipher.md](description/Cipher.md).

**Tip:** As there are several specific encryption algorithms to be implemented, we recommend implementing the simplest one first (None-Cipher) and then taking care of the `User` and `Config` classes described below. All encryption algorithms can also be easily checked using the [Test option](#Test) at program startup.

#### Users & Messages

Users of the messaging service can send and receive encrypted messages and are represented in this program by the class `User` to be written. A detailed description of this class can be found at [description/User_Messages.md](description/User_Messages.md).

#### Config

Once the above classes have been implemented, the configuration file can be read in. A detailed description of the structure of the configuration file can be found under [description/Config.md](description/Config.md). This file also describes what the corresponding class called `Config` should look like.



---

### Program start

**ATTENTION: The file `main.cpp` must NOT be changed!**

The program start is already given in the file `main.cpp`. When called, the program receives the path to the configuration file as a parameter. After that, an object of class `Config` (to be implemented) is created, the file is checked and an attempt is made to parse the configuration file (reading in the users and their contacts).

If the configuration file was read in successfully, the user can choose between the options _Registration_, _Login_ and _Test_.

### Registration

> already implemented in main.cpp

If registration is selected for the first entry, the `userRegistration` function is called and user name and password must be entered. The user name is checked to see whether die:der User:in already exists in the configuration file. If not, then the:the user:in should be registered with the function call `config.registerUser(username, password)`. This function is e.g. to be implemented in the `Config` class.

The return value of the `userRegistration` function in the `main.cpp` file should be a pointer to the `User` object representing the newly registered user.

#### Example

```
Welcome to the OOP1 Messaging Service!
Would you like to [r]egister, [l]ogin or [t]est?
  > r
Please enter user name!
  > Max
Please enter your password!
  > easypassword


Choose your option: [a]dd contact, [e]ncrypt, [d]ecrypt, [s]how or [q]uit
  > 
```



### Log in

> already implemented in main.cpp

If the login is selected for the first entry, the `userLogin` function is called and the user name must first be entered. The configuration file is checked to see whether this name exists. If this is the case, the:the user:in has three chances to enter the correct password. For this, the function `config.loginUser(username, password)` is called, which has to be implemented. This returns a pointer to the corresponding `User` object if the login was successful and `nullptr` if the password does not match the one in the configuration file. (`nullptr` is the C++ equivalent of `NULL`.)

The return value of the `userLogin` function in the `main.cpp` file should be the newly created and logged in user or `nullptr` if the login was unsuccessful.

```
Welcome to the OOP1 Messaging Service!
Would you like to [r]egister, [l]ogin or [t]est?
  > l
Please enter user name!
  > David
Please enter your password!
  > easypassword


Choose your option: [a]dd contact, [e]ncrypt, [d]ecrypt, [s]how or [q]uit
  > 
```



### Trial

> already implemented in main.cpp

If test is selected the first time you enter, the messaging service will not be accessed. This option is only used to test the encryption algorithms to be implemented without the need for other classes.

#### Example

```
Welcome to the OOP1 Messaging Service!
Would you like to [r]egister, [l]ogin or [t]est?
   > t
What cipher would you like to use?
   > caesar
Enter your message now:
   > hello world

Sending...
INCKVLLWMM
Reading...
Recipient: SYSTEM
Transmitter: SYSTEM
HELLOWORLD
```



### Menu

> already implemented in main.cpp

If the registration or the login was successful, the:the user:in comes to the main menu. This is also already fully implemented. A detailed description of the menu can be found under [description/Menu.md](description/Menu.md).



### End of program

This part is already implemented. However, it is yet to be implemented when a configuration file is invalid.

| return value | Description |
| ------------ | -------------------------------------------------- ---------- |
| 0 | Normal end of program |
| 1 | Memory could not be allocated. Error message: `Error: not enough memory!\n` |
| 2 | Incorrect number of program arguments. Error message: `Usage: ./a1 <configfile>\n` |
| 3 | Configuration file could not be opened. Error message: `Error: could not open config file!\n` |
| 4 | Invalid configuration file. Error message: `Error: invalid config file!\n` |
| 5 | Login failed after three failed attempts |





## A notice

> An important note at the end: All cryptographic methods used in this example are by no means secure and should under no circumstances be used in security-critical applications. Due to the configuration file, all keys can also be viewed publicly. Therefore, anyone with access to the configuration file can see every key and thus decrypt every message. If you are interested in modern cryptographic methods, which are significantly more complex than those used here, we refer you to the "Information Security" course.
