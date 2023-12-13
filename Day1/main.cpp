#include "aoc/helpers.h"

namespace {
  using Result = std::pair<int, int>;
  using MappedFileSource = aoc::MappedFileSource<char>;

  constexpr std::string_view SampleInput(R"(91212129)");
  constexpr int SR_Part1 = 9; // 9 == 9
  constexpr int SR_Part2 = 6; // (1 + 2) + (1 + 2)

  const auto GetSum = [](std::string_view f) {
    char last = -1;
    int64_t sum = 0;
    for (auto c : f) {
      if (last == c) {
        sum += aoc::ctoi(c);
      }
      last = c;
    }

    if (f.front() == f.back()) {
      sum += aoc::ctoi(f.front());
    }
    return sum;
  };

  const auto GetSum2 = [](std::string_view f) {
    int64_t sum = 0;
    const auto dist = f.size() / 2;
    for (size_t i = 0; i < dist; ++i) {
      if (f[i] == f[i + dist]) {
        sum += aoc::ctoi(f[i]) + aoc::ctoi(f[i + dist]);
      }
    }
    return sum;
  };

  const auto LoadInput = [](auto f) {
    Result r{0, 0};
    std::string_view line;
    while (aoc::getline(f, line)) {
      r.first += GetSum(line);
      r.second += GetSum2(line);
    }
    return r;
  };
}

int main(int argc, char** argv) {
  aoc::AutoTimer t;
  const bool inTest = argc < 2;

  Result r;
  if (inTest) {
    r = LoadInput(SampleInput);
  } else {
    std::unique_ptr<MappedFileSource>m(new MappedFileSource(argc, argv));
    std::string_view f(m->data(), m->size());
    r = LoadInput(f);
  }

  int part1 = 0;
  int part2 = 0;

  std::tie(part1, part2) = r;

  aoc::print_results(part1, part2);

  if (inTest) {
    aoc::assert_result(part1, SR_Part1);
    aoc::assert_result(part2, SR_Part2);
  }

  return 0;
}
