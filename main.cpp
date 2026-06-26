#include <chrono>
#include <generator>
#include <gmp.h>
#include <gmpxx.h>
#include <iostream>
#include <vector>

std::generator<const mpz_class &> fibonacci_generator(int n) {
  mpz_class a, b;
  a = 0;
  b = 1;
  if (n >= 0) {
    co_yield a;
  }
  if (n >= 1) {
    co_yield b;
  }

  mpz_class result;
  for (int i = 0; i < n - 1; i++) {
    result = a + b;
    a = b;
    b = result;
    co_yield result;
  }
}

std::vector<mpz_class> fibonacci_array(int n) {
  std::vector<mpz_class> result{};

  mpz_class a, b;
  a = 0;
  b = 1;
  if (n >= 0) {
    result.push_back(a);
  }
  if (n >= 1) {
    result.push_back(b);
  }

  for (int i = 0; i < n - 1; i++) {
    mpz_class c = a + b;
    a = b;
    b = c;
    result.push_back(c);
  }
  return result;
}

int main(int argc, char *argv[]) {
  bool generator = false;
  bool trivial = false;
  bool array = false;

  bool runtime = false;

  int number = 0;
  bool haveNumber = false;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "--generator") {
      if (trivial || array) {
        std::cerr
            << "Usage: " << argv[0]
            << " <number> (--generator | --trivial | --array) [--runtime]\n";
        return 1;
      }
      generator = true;
    } else if (arg == "--trivial") {
      if (generator || array) {
        std::cerr
            << "Usage: " << argv[0]
            << " <number> (--generator | --trivial | --array) [--runtime]\n";
        return 1;
      }
      trivial = true;
    } else if (arg == "--array") {
      if (trivial || generator) {
        std::cerr
            << "Usage: " << argv[0]
            << " <number> (--generator | --trivial | --array) [--runtime]\n";
        return 1;
      }
      array = true;
    } else if (!haveNumber) {
      try {
        number = std::stoi(arg);
        haveNumber = true;
      } catch (...) {
        std::cerr << "Invalid number: " << arg << '\n';
        return 1;
      }
    } else if (arg == "--runtime") {
      runtime = true;
    } else {
      std::cerr << "Unexpected argument: " << arg << '\n';
      return 1;
    }
  }

  if (!haveNumber || (!generator && !trivial && !array)) {
    std::cerr << "Usage: " << argv[0]
              << " <number> (--generator | --trivial | --array) [--runtime]\n";
    return 1;
  }

  if (runtime) {

    if (generator) {
      auto t1 = std::chrono::high_resolution_clock::now();
      for (auto x : fibonacci_generator(number)) {
        asm("");
      }
      auto t2 = std::chrono::high_resolution_clock::now();
      auto ms_int = duration_cast<std::chrono::milliseconds>(t2 - t1);
      std::cout << ms_int.count() << "ms\n";
    } else if (array) {
      auto t1 = std::chrono::high_resolution_clock::now();
      for (auto x : fibonacci_array(number)) {
        asm("");
      }
      auto t2 = std::chrono::high_resolution_clock::now();
      auto ms_int = duration_cast<std::chrono::milliseconds>(t2 - t1);
      std::cout << ms_int.count() << "ms\n";
    } else if (trivial) {
      auto t1 = std::chrono::high_resolution_clock::now();
      mpz_class a, b, result;
      a = 0;
      b = 1;
      for (int i = 0; i < number - 1; i++) {
        result = a + b;
        a = b;
        b = result;
        asm("");
      }
      auto t2 = std::chrono::high_resolution_clock::now();
      auto ms_int = duration_cast<std::chrono::milliseconds>(t2 - t1);
      std::cout << ms_int.count() << "ms\n";
    }
  } else {
    if (generator) {
      for (auto x : fibonacci_generator(number)) {
        std::cout << x << '\n';
      }
    } else if (array) {
      for (auto x : fibonacci_array(number)) {
        std::cout << x << '\n';
      }
    } else if (trivial) {
      mpz_class a, b, result;
      a = 0;
      b = 1;
      for (int i = 0; i < number - 1; i++) {
        result = a + b;
        a = b;
        b = result;
        std::cout << result << '\n';
      }
    }
  }

  return 0;
}
