#include <boost/asio.hpp>
#include <iostream>

struct Stranded {

  Stranded(boost::asio::io_context &Ioc)
      : Timer(Ioc), Strand(Ioc.get_executor()), running(false) {
    Timer.expires_from_now(std::chrono::seconds(1));
  }

  boost::asio::awaitable<void> spawn() {
    for (;;) {

      co_await Timer.async_wait(boost::asio::use_awaitable);

      std::cout << (running ? "running" : "stopped") << std::endl;

      Timer.expires_from_now(std::chrono::seconds(1));
    }
  }

  void run() { boost::asio::co_spawn(Strand, spawn(), boost::asio::detached); }

  void setRunning(bool Running) {
    boost::asio::post(Strand, [this, Running] { running = Running; });
  }

  boost::asio::steady_timer Timer;
  boost::asio::strand<boost::asio::any_io_executor> Strand;
  bool running;
};

int main() {

  // Create a context
  boost::asio::io_context ioc;

  Stranded myStrand(ioc);
  myStrand.run();

  auto T1 = std::thread([&]() { ioc.run(); });

  for (size_t i = 1; i < 10; i++) {
    myStrand.setRunning(i % 2);
    std::this_thread::sleep_for(std::chrono::seconds(5));
  }
  T1.join();
}
