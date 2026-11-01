#include <charconv>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <optional>
#include <string_view>
#include <system_error>

std::optional<int> parse_int(std::string_view str) {
  int value{};

  auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), value);

  if (ec == std::errc::result_out_of_range) {
    std::cerr << "Integer out of range\n";
    return std::nullopt;
  }

  if (ec != std::errc{} || ptr != str.data() + str.size()) {
    std::cerr << "Invalid integer: " << str << '\n';
    return std::nullopt;
  }

  return value;
}

std::optional<int> input(char name) {
  int value{};

  std::cout << "Input " << name << ": ";

  if (!(std::cin >> value)) {
    std::cerr << "Invalid input\n";
    return std::nullopt;
  }

  return value;
}

__declspec(noinline) std::optional<int> sum(int a, int b) noexcept {
  constexpr int min = std::numeric_limits<int>::min();
  constexpr int max = std::numeric_limits<int>::max();

  if ((b > 0 && a > max - b) || (b < 0 && a < min - b))
    return std::nullopt;

  return a + b;
}

int main(int argc, char **argv) {
  std::optional<int> a;
  std::optional<int> b;

  if (argc > 1) {
    a = parse_int(argv[1]);

    if (!a)
      return EXIT_FAILURE;
  }

  if (argc > 2) {
    b = parse_int(argv[2]);

    if (!b)
      return EXIT_FAILURE;
  }

  if (!a)
    a = input('a');

  if (!b)
    b = input('b');

  if (!a || !b)
    return EXIT_FAILURE;

  auto result = sum(*a, *b);

  if (!result) {
    std::cerr << "Integer overflow\n";
    return EXIT_FAILURE;
  }

  std::cout << *result << '\n';

  return EXIT_SUCCESS;
}
