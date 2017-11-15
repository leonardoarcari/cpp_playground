#pragma once

#include <memory>
#include <set>
#include <string>

namespace primer {
class Quote;
class Disc_quote;
class Basket;
double print_total(std::ostream &, const Quote &, std::size_t);
}

class Quote {
public:
  Quote() = default;
  Quote(const std::string &book, double sales_price)
      : bookNo(book), price(sales_price) {}
  Quote(const Quote &) = default;
  Quote(Quote &&) = default;
  Quote &operator=(const Quote &) = default;
  Quote &operator=(Quote &&) = default;
  std::string isbn() const { return bookNo; }
  virtual double net_price(std::size_t n) const { return n * price; }
  virtual ~Quote() = default;

private:
  std::string bookNo; // ISBN number of this item
protected:
  double price = 0.0; // normal, undiscounted price
};

class Disc_quote : public Quote {
public:
  Disc_quote() = default;
  Disc_quote(const std::string &book, double price, std::size_t qty,
             double disc)
      : Quote(book, price), quantity(qty), discount(disc) {}
  double net_price(std::size_t) const = 0;

protected:
  std::size_t quantity = 0; // purchase size for the discount to apply
  double discount = 0.0;
};

class Bulk_quote : public Disc_quote {
public:
  Bulk_quote() = default;
  Bulk_quote(const std::string &book, double price, std::size_t qty,
             double disc)
      : Disc_quote(book, price, qty, disc) {}
  double net_price(std::size_t) const override;
  ~Bulk_quote();
};

class Basket {
public:
  // Basket uses synthetized default ctor and copy-control members
  void add_item(const std::shared_ptr<Quote> &sale) { items.insert(sale); }
  // prints the toal price for each book and the overall total for all items in
  // the basket
  double total_receipt(std::ostream &) const;

private:
  // function to compare shared_ptrs needed by the multiset member
  static bool compare(const std::shared_ptr<Quote> &lhs,
                      const std::shared_ptr<Quote> &rhs) {
    return lhs->isbn() < rhs->isbn();
  }
  // multiset to hold multiple quotes, ordered by the compare member
  std::multiset<std::shared_ptr<Quote>, decltype(compare) *> items{compare};
};

double print_total(std::ostream &, const Quote &, std::size_t);
