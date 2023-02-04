#include <chrono>
#include <iostream>

class ExecutionTimer {
public:
  // using Clock = std::conditional_t<std::chrono::high_resolution_clock::is_steady,
  //                                  std::chrono::high_resolution_clock,
  //                                  std::chrono::steady_clock>;

private:
  std::chrono::steady_clock::time_point start;

public:
  ExecutionTimer() {
    start = std::chrono::steady_clock::now();
  }
  ~ExecutionTimer() {
    const auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
  }

  void stop() {
    const auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

    start = end;
  }
};