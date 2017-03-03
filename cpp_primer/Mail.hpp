#pragma once
#include <ostream>
#include <set>
#include <string>

namespace primer {
class Folder;
class Message {
  friend class Folder;
  friend void swap(Message &, Message &);
  friend std::ostream &print(std::ostream &, const Message &);

public:
  // folders is implicity initialized to the empty set
  explicit Message(const std::string &str = "");
  Message(const Message &);
  Message &operator=(const Message &);
  ~Message();

  // add/remove this Message from the specified Folder's set of messages
  void save(Folder &);
  void remove(Folder &);

private:
  std::string contents;       // actual message text
  std::set<Folder *> folders; // Folders that have this Message

  // utility functions used by copy constructor, assignment and destructor
  // add this Message to the Folders that point to the parameter
  void add_to_Folders(const Message &);
  // remove this Message from every Folder in folders
  void remove_from_Folders();
};

class Folder {
  friend void swap(Folder &, Folder &);

public:
  explicit Folder(const std::string &);
  Folder(const Folder &);
  Folder &operator=(const Folder &);
  ~Folder();

  void addMsg(Message *);
  void remMsg(Message *);
  const std::string &getName() const { return name; }

private:
  std::string name;
  std::set<Message *> msgs;

  void add_to_Messages(const Folder &);
  void remove_from_Messages();
};
}