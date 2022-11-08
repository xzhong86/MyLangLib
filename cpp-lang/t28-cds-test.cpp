
#include <any>
#include <string>
#include <vector>
#include <map>

// a simple implementation for common structured data, base on c++17 (std::any)
namespace cds {
  using Bool    = bool;
  using Integer = long long int;
  using Double  = double; // or use Float as name?
  using String  = std::string;
  using Value   = std::any;

  class Any;
  using Array   = std::vector<Any>;
  using Table   = std::map<String, Any>; // only use string as key

  class Any : public std::any {
  public:
      using std::any::any;

      template <typename T>
      T as() const { return std::any_cast<T>(*this); }

      // as table when use string index, as array when use integer index
      Any operator[](const String &key) { return as<Table>()[key]; }
      Any operator[](size_t index)      { return as<Array>()[index]; }

      bool isBool()    const { return this->type() == typeid(Bool); }
      bool isInteger() const { return this->type() == typeid(Integer); }
      bool isDouble()  const { return this->type() == typeid(Double); }
      bool isString()  const { return this->type() == typeid(String); }
      bool isArray()   const { return this->type() == typeid(Array); }
      bool isTable()   const { return this->type() == typeid(Table); }

      Bool    to_b() const { return as<Bool>(); }
      Integer to_i() const { return as<Integer>(); }
      Double  to_f() const { return as<Double>(); }
      String  to_s() const { return as<String>(); }
  };

  Integer operator "" _I(unsigned long long int v)   { return Integer(v); }
  Double  operator "" _F(unsigned long long int v)   { return Double(v); }
  Double  operator "" _F(long double v) { return Double(v); }
  String  operator "" _S(const char *s, size_t l) { return String(s, l); }

  Value getByPath(const Table&, const String &);
}

#include <iostream>

// g++ -Wall -O2 -std=c++17 t28-cds-test.cpp
int main() {
  using namespace cds;
  Table tab;
  tab["aaa"] = 111_I;
  tab["bbb"] = Table{ {"aa", 11_I }, {"bb", "22"_S }, { "cc", 3.3_F } };

  Array arr = { 11_I, 22_F, 33_I, 44_F, "ee"_S };
  arr.push_back("str");
  tab["arr"] = arr;

  std::cout << "tab[bbb] is table: " << tab["bbb"].isTable() << std::endl;
  std::cout << "tab[aaa].type.name: " << tab["aaa"].type().name() << std::endl;
  std::cout << "tab[aaa] is Integer: " << tab["aaa"].isInteger() << std::endl;
  std::cout << "tab[aaa] value: " << tab["aaa"].to_i() << std::endl;

  std::cout << "tab[bbb][bb] type name: " << tab["bbb"]["bb"].type().name() << std::endl;
  std::cout << "tab[bbb][bb] is string: " << tab["bbb"]["bb"].isString() << std::endl;

  std::cout << "tab[bbb][cc] type name: " << tab["bbb"]["cc"].type().name() << std::endl;
  std::cout << "tab[bbb][cc] value: " << tab["bbb"]["cc"].to_f() << std::endl;

  std::cout << "tab[arr][1] type name: " << tab["arr"][1].type().name() << std::endl;
  std::cout << "tab[arr][1] value: " << tab["arr"][1].to_f() << std::endl;
 
  tab["bool"] = true;
  std::cout << "tab[bool] type name: " << tab["bool"].type().name() << std::endl;
  std::cout << "tab[bool] value: " << tab["bool"].to_b() << std::endl;
}

