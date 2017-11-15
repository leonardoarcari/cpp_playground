#include "Mail.hpp"
#include <iostream>

int main(int argc, char const *argv[]) {
  auto m1 = primer::Message("Ciao - M1");
  auto m2 = primer::Message("Ciao - M2");
  auto f1 = primer::Folder("Folder1");
  auto f2 = primer::Folder("Folder2");
  m1.save(f1);
  m2.save(f2);
  print(std::cout, m1);
  print(std::cout, m2);
  auto m3 = m1;
  print(std::cout, m3);
  m2 = m3;
  print(std::cout, m2);
  print(std::cout, m3);
  auto m4 = primer::Message("Ciao - M4");
  m4.save(f2);
  print(std::cout, m4);
  swap(m1, m4);
  print(std::cout, m1);
  print(std::cout, m4);
  auto m5 = primer::Message("Ciao - M5");
  m5.save(f1);
  m5.save(f2);
  print(std::cout, m5);

  return 0;
}

namespace primer {

/*******************************************************************************
 * Message implementation
 ******************************************************************************/

Message::Message(const std::string &str) : contents(str) {}

Message::Message(const Message &m) : contents(m.contents), folders(m.folders) {
  add_to_Folders(m);
}

Message::~Message() { remove_from_Folders(); }

Message &Message::operator=(const Message &rhs) {
  // handle self-assignment by removing pointers before inserting them
  remove_from_Folders();   // update existing Folders
  contents = rhs.contents; // copy message contents from rhs
  folders = rhs.folders;   // Folder pointers from rhs
  add_to_Folders(rhs);     // add this Message to those Folders
  return *this;
}

void Message::save(Folder &f) {
  folders.insert(&f); // add the fiven Folder to our list of Folders
  f.addMsg(this);     // add this Messafe to f's set of Messages
}

void Message::remove(Folder &f) {
  folders.erase(&f); // take the fiven Folder out of our list of Folders
  f.remMsg(this);
}

void Message::add_to_Folders(const Message &m) {
  for (auto f : m.folders)
    f->addMsg(this);
}

void Message::remove_from_Folders() {
  for (auto f : folders) {
    f->remMsg(this);
  }
  folders.clear();
}

void swap(Message &lhs, Message &rhs) {
  using std::swap; // Good habit

  // remove pointers to each Message from their (original) respective Folders
  for (auto f : lhs.folders)
    f->remMsg(&lhs);
  for (auto f : rhs.folders)
    f->remMsg(&rhs);
  // swap the contents and Folder pointers sets
  swap(lhs.folders, rhs.folders);   // uses swap(set&, set&)
  swap(lhs.contents, rhs.contents); // uses swap(string&, string&)

  // add pointers to each Message to their (new) respective Folders
  for (auto f : lhs.folders)
    f->addMsg(&lhs);
  for (auto f : rhs.folders)
    f->addMsg(&rhs);
}

std::ostream &print(std::ostream &os, const Message &m) {
  os << "Message content:\n"
     << m.contents << "\n Contained in "
     << (m.folders.size() < 2 ? "folder" : "folders") << ": ";

  for (auto f : m.folders)
    os << f->getName() << (f != *(--m.folders.end()) ? ", " : "");

  return os << '\n';
}

/*******************************************************************************
 * Folder implementation
 ******************************************************************************/

Folder::Folder(const std::string &n) : name(n) {}
Folder::Folder(const Folder &f) : name(f.name), msgs(f.msgs) {
  add_to_Messages(f);
}

Folder &Folder::operator=(const Folder &rhs) {
  remove_from_Messages();
  msgs = rhs.msgs;
  name = rhs.name;
  add_to_Messages(rhs);
  return *this;
}

Folder::~Folder() { remove_from_Messages(); }

void Folder::addMsg(Message *m) { msgs.insert(m); }
void Folder::remMsg(Message *m) { msgs.erase(m); }

void Folder::add_to_Messages(const Folder &f) {
  for (auto m : f.msgs)
    m->folders.insert(this);
}

void Folder::remove_from_Messages() {
  for (auto m : msgs)
    m->folders.erase(this);
}

void swap(Folder &lhs, Folder &rhs) {
  using std::swap;

  for (auto m : lhs.msgs)
    m->remove(lhs);
  for (auto m : rhs.msgs)
    m->remove(rhs);

  swap(lhs.name, rhs.name);
  swap(lhs.msgs, rhs.msgs);

  for (auto m : lhs.msgs)
    m->save(lhs);
  for (auto m : rhs.msgs)
    m->save(rhs);
}
}