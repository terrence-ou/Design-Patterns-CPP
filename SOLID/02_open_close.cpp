/*
2 - Open-close Principle
*/

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

enum class Color { red, green, blue };
enum class Size { small, medium, large };

struct Product {
  string name{};
  Color color{};
  Size size{};
};

/* Bad filter implementation: */
struct ProductFilter {
  typedef vector<Product *> Items;

  Items byColor(Items items, const Color color) {
    Items result{};
    for (auto &i : items) {
      if (i->color == color) result.push_back(i);
    }
    return result;
  }

  Items bySize(Items items, const Size size) {
    Items result{};
    for (auto &i : items) {
      if (i->size == size) result.push_back(i);
    }
    return result;
  }

  Items bySizeAndColor(Items items, const Size size, const Color color) {
    Items result{};
    for (auto &i : items) {
      if (i->size == size && i->color == color) result.push_back(i);
    }
    return result;
  }
};

/* Better filter implementation */
template <typename T>
struct Specification {
  virtual ~Specification() = default;
  virtual bool is_satisfied(T *item) const = 0;
};

struct ColorSpecification : Specification<Product> {
  Color color{};
  explicit ColorSpecification(const Color color) : color{color} {}
  bool is_satisfied(Product *item) const override {
    return item->color == color;
  }
};

struct SizeSpecification : Specification<Product> {
  Size size{};
  explicit SizeSpecification(const Size size) : size{size} {}
  bool is_satisfied(Product *item) const override { return item->size == size; }
};

template <typename T>
struct Filter {
  virtual vector<T *> filter(vector<T *> items);
};
