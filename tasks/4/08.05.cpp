#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>
#include <cassert>

template <typename D = std::chrono::duration<double>>
class Timer {
public:
  Timer() : m_running(false) {}

  void start() {
    if (!m_running) {
      m_running = true;
      m_begin = std::chrono::steady_clock::now();
    }
  }

  void stop() {
    if (m_running) {
      auto end = std::chrono::steady_clock::now();
      m_durations.push_back(std::chrono::duration_cast<D>(end - m_begin));
      m_running = false;
    }
  }

  double average() const {
    if (m_durations.empty()) {
      return 0.0;
    }
    double sum = 0.0;
    for (const auto& duration : m_durations) {
      sum += duration.count();
    }
    return sum / m_durations.size();
  }
  
  void clear() {
      m_durations.clear();
  }

private:
  using clock_t = std::chrono::steady_clock;

  bool m_running;
  clock_t::time_point m_begin;
  std::vector<D> m_durations;
};

auto calculate(std::size_t size)
{
	auto x = 0.0;
	for (auto i = 0uz; i < size; ++i)
	{
		x += std::pow(std::sin(i), 2) + std::pow(std::cos(i), 2);
	}
	return x;
}

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}


int main() {
  Timer timer;
  const int num_runs = 10;

  for (int i = 0; i < num_runs; ++i) {
    timer.start();
    assert(equal(calculate(100000), 100000));
    timer.stop();
  }

  std::cout << "Average time over " << num_runs << " runs: " << timer.average() << "s" << std::endl;
  
  return 0;
}
