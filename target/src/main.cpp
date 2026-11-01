#include <iostream>
#include <optional>
#include <string_view>

bool handle_ec(const char *ptr, std::errc &ec) noexcept;

int input(char c) noexcept;

bool parse_int(std::optional<int> &parsed, int argc, char **argv);

int sum(int a, int b) noexcept { return a + b; }

int main(int argc, char **argv) {
  std::optional<int> a;
  std::optional<int> b;

  if (argc > 1) {

    if (!parse_int(a, 1, argv)) {
      return EXIT_FAILURE;
    }

    if (argc > 2) {

      if (!parse_int(b, 2, argv)) {
        return EXIT_FAILURE;
      }
    }
  }

  if (!a.has_value()) {
    a = input('a');
  }

  if (!b.has_value()) {
    b = input('b');
  }

  std::cout << sum(*a, *b);

  return EXIT_SUCCESS;
}

int input(char c) noexcept {
  int input;

  std::cout << "Input " << c << ": ";
  std::cin >> input;

  return input;
}

bool handle_ec(const char *ptr, std::errc &ec) noexcept {
  if (ec == std::errc::invalid_argument) {
    std::cout << "Argument is not integer!" << std::endl;

    return false;
  } else if (ec == std::errc::result_out_of_range) {
    std::cout << "Number is very big for integer" << std::endl;

    return false;
  }

  return true;
}

bool parse_int(std::optional<int> &parsed, int argc, char **argv) {
  std::string_view arg_str = argv[argc];

  parsed.emplace();
  auto [ptr, ec] =
      std::from_chars(arg_str.data(), arg_str.data() + arg_str.size(), *parsed);

  return handle_ec(ptr, ec);
}
