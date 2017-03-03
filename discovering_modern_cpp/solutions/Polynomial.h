#include <initializer_list>
#include <iterator>
#include <vector>

#ifndef EXERCISES_DISCOVERING_MODERN_CPP_POLYNOMIAL_H
#define EXERCISES_DISCOVERING_MODERN_CPP_POLYNOMIAL_H

class Polynomial {
public:
  using size_type = std::vector<double>::size_type;

  explicit Polynomial(int degree);
  Polynomial(const Polynomial &poly) = default;
  Polynomial(std::initializer_list<double> list);

  ~Polynomial();

  Polynomial &operator=(const Polynomial &src);
  Polynomial &operator=(Polynomial &&src);

  double &operator[](size_type i);
  const double &operator[](size_type i) const;

  friend std::ostream &operator<<(std::ostream &os, const Polynomial &poly);
  static Polynomial f(double c2, double c1, double c0);

private:
  int m_degree;
  std::vector<double> m_coefficients;
};

#endif // EXERCISES_DISCOVERING_MODERN_CPP_POLYNOMIAL_H