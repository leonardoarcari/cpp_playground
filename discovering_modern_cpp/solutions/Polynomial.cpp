#include "./Polynomial.h"
#include <cassert>
#include <iostream>
#include <string>

Polynomial::Polynomial(int degree)
    : m_degree{degree}, m_coefficients{std::vector<double>{}} {
  for (int i = 0; i <= degree; ++i) {
    m_coefficients.push_back(0);
  }
}

Polynomial::Polynomial(std::initializer_list<double> list)
    : m_degree{static_cast<int>(list.size() - 1)},
      m_coefficients{std::vector<double>{list}} {}

Polynomial::~Polynomial() {}

Polynomial &Polynomial::operator=(const Polynomial &src) {
  m_degree = src.m_degree;
  m_coefficients.clear();
  std::copy(std::begin(src.m_coefficients), std::end(src.m_coefficients),
            std::back_inserter(m_coefficients));
  return *this;
}

double &Polynomial::operator[](Polynomial::size_type i) {
  return m_coefficients[i];
}

const double &Polynomial::operator[](Polynomial::size_type i) const {
  return m_coefficients[i];
}

std::ostream &operator<<(std::ostream &os, const Polynomial &poly) {
  std::string out_string{};
  auto coeff = poly.m_coefficients;
  for (unsigned int i = 0; i < coeff.size(); ++i) {
    i == coeff.size() - 1 ? out_string.append(std::to_string(coeff[i]))
                          : out_string.append(std::to_string(coeff[i]) + ", ");
  }
  return os << out_string;
}

Polynomial &Polynomial::operator=(Polynomial &&src) {
  m_degree = src.m_degree;
  std::swap(m_coefficients, src.m_coefficients);
  std::cout << "Move assignment operator" << std::endl;
  return *this;
}

Polynomial Polynomial::f(double c2, double c1, double c0) {
  return Polynomial{c2, c1, c0};
}