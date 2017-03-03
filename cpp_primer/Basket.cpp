#include "Basket.hpp"
#include <memory>
#include <ostream>

int main(int argc, char const *argv[]) {
  auto bsk = Basket{};
  bsk.add_item(std::make_shared<Quote>("123", 45));
}

/****************************************************/

double Basket::total_receipt(std::ostream &os) const {
  double sum = 0.0;

  // iter refers to the first element in a batch of elements with the same
  // ISBN
  // upper_bound returns an iterator to the element just past the end of the
  // batch
  for (auto iter = items.cbegin(); iter != items.cend();
       iter = items.upper_bound(*iter)) {
    sum += print_total(os, **iter, items.count(*iter));
  }
  os << "Total Sale: " << sum << '\n';
  return sum;
}

double print_total(std::ostream &os, const Quote &item, std::size_t n) {
  double ret = item.net_price(n);
  os << "ISBN: " << item.isbn() << "# sold: " << n << " total due: " << ret
     << '\n';
  return ret;
}
