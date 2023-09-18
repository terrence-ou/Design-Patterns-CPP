/*
3 - Liskov Substitution Principle
*/

#include <cmath>
#include <iostream>
#include <string>
#include <typeinfo>
using std::cout;
using std::endl;
using std::string;

/* ============== BAD EXAMPLE ============ */

// We declare a super class Ellipse
class Ellipse {
 protected:
  int a{}, b{};

 public:
  Ellipse(int a, int b) : a{a}, b{b} {};

  // getters
  int get_long_axis() const { return this->a; }
  int get_short_axis() const { return this->b; }

  // setters
  virtual void set_long_axis(int a) { this->a = a; }
  virtual void set_short_axis(int b) { this->b = b; }

  double get_area() const { return M_PI * this->a * this->b; }
};

// Circle inherits Ellipse
// This is a bad idea to inherit circle from ellips in this case,
// because inherited setters may cause the unwanted value change in Circle.
// Please refer to
class Circle : public Ellipse {
 public:
  Circle(int radius) : Ellipse(radius, radius) {}
  void set_long_axis(int a) override {
    this->a = a;
    this->b = a;
  }
  void set_short_axis(int b) override {
    this->a = b;
    this->b = b;
  }
};

void process_ellipse(Ellipse &shape) {
  int long_axis = shape.get_long_axis();
  // There might be a behavior that changes the value of short axis:
  shape.set_short_axis(10);
  cout << "Expected area: " << (M_PI * long_axis * 10)
       << ", got: " << shape.get_area() << endl;
}

/* ============== BETTER EXAMPLE ============ */

// A better way is use a more general super class,
// and define different behaviors for ellipse and circle
class ClosedTypeShape {
 public:
  virtual double area() const = 0;
  virtual string getType() const { return "ClosedTypeShape"; }
};

class BetterEllipse : public ClosedTypeShape {
 private:
  int a{}, b{};

 public:
  BetterEllipse(int a, int b) : a{a}, b{b} {}
  string getType() const override { return "BetterEllipse"; }
  // getters
  int get_long_axis() { return this->a; }
  int get_short_axis() { return this->b; }
  // setters
  void set_long_axis(int a) { this->a = a; }
  void set_short_axis(int b) { this->b = b; }

  double area() const override { return M_PI * a * b; }
};

class BetterCircle : public ClosedTypeShape {
 private:
  int r;

 public:
  BetterCircle(int r) : r{r} {};
  string getType() const override { return "BetterCircle"; }
  int get_radius() { return this->r; }
  void set_radius(int r) { this->r = r; }

  double area() const override { return M_PI * r * r; }
};

void process_closed_shape(ClosedTypeShape &shape) {
  cout << "The area of " << shape.getType() << " instance is " << shape.area()
       << endl;
}

/* ============== Main program ============*/
int main() {
  cout << "Results of the bad example:" << endl;
  Ellipse shape_a{2, 8};
  Circle shape_b{6};
  process_ellipse(shape_a);
  process_ellipse(shape_b);

  cout << "\nResults of the better example: " << endl;
  BetterEllipse shape_c{2, 8};
  BetterCircle shape_d{6};
  process_closed_shape(shape_c);
  process_closed_shape(shape_d);
  return 0;
}
