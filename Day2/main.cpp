#include "aoc/helpers.h"

namespace {
  using Result = std::pair<int, int>;
  using MappedFileSource = aoc::MappedFileSource<char>;

  constexpr std::string_view SampleInput(R"(5 9 2 8
9 4 7 3
3 8 6 5)");
  constexpr int SR_Part1 = 18;
  constexpr int SR_Part2 = 9;

  const auto ChecksumRow = [](std::string_view row) {
    int32_t max = INT32_MIN;
    int32_t min = INT32_MAX;

    aoc::parse_as_integers(row, " \t", [&](const auto n) {
      max = std::max(static_cast<int32_t>(n), max);
      min = std::min(static_cast<int32_t>(n), min);
    });

    DEBUG_PRINT("line: " << row << " min: " << min << ", max: " << max << ", diff: " << max - min);

    return max - min;
  };

  const auto EvenlyDivisible = [](int32_t a, int32_t b) {
    const auto dividend = std::max(a, b);
    const auto divisor = std::min(a, b);
    const int64_t r = dividend % divisor ? 0 : dividend / divisor;
    return r;
  };

  const auto ChecksumRow2 = [](std::string_view row) {

    std::vector<int32_t> nums;
    aoc::parse_as_integers(row, " \t", [&](const auto n) {
      nums.push_back(n);
    });

    for (size_t i = 0; i < nums.size() - 1; ++i) {
      for (size_t j = i + 1; j < nums.size(); ++j) {
        const auto r = EvenlyDivisible(nums[i], nums[j]);
        if (r) {
          return r;
        }
      }
    }
    return int64_t{};
  };

  const auto LoadInput = [](auto f) {
    Result r{0, 0};
    std::string_view line;
    while (aoc::getline(f, line)) {
      r.first += ChecksumRow(line);
      r.second += ChecksumRow2(line);
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
