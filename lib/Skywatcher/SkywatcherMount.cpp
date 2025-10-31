#include <Skywatcher/Skywatcher.h>
#include <Skywatcher/SkywatcherMount.h>
#include <atomic>
#include <boost/asio.hpp>

using namespace me;

// Each axis in the skywatcher mount operates independently. The encoder
// position of the mount is updated every 'tick' of the clock.
// There is a hardware timer which generates a stepping pulse to the motor
// which is based on the clock's frequency as well and the preset value.

struct SkywatcherAxis {
private:
  /// @brief Strand for ensuring that the modifications do not happen
  /// concurrently
  boost::asio::strand<boost::asio::any_io_executor> Strand;

  /// @brief Timer for updating the encoder position
  boost::asio::steady_timer Timer;

  /// @brief Current encoder position of the mount
  uint32_t EncoderPosition;

  /// @brief Desired encoder position of the mount
  uint32_t TargetEncoderPosition;

  /// @brief Desired encoder position of the mount in GoTo mode
  uint32_t GoToEncoderPosition;

  /// @brief The mode of the mount
  skywatcher::MotionMode Mode;

  /// @brief The number of ticks of the clock before an encoder step is sent
  uint32_t TicksPerStep;

  /// @brief The AutoGuide speed of the mount
  skywatcher::AutoGuideSpeed GuideSpeed;

  /// @brief The direction of the mount
  bool Forward;

  void moveAxis() {}

  boost::asio::awaitable<void> runTimer() {
    for (;;) {
      try {

        // wait for timer to expire
        co_await Timer.async_wait(boost::asio::use_awaitable);

        // Move the axis
        moveAxis();

        // set the timer to expire again
        Timer.expires_from_now(std::chrono::nanoseconds(100));

      } catch (boost::system::error_code &) {
        // timer expired so just restart the loop
      }
    }
  }

public:
  /// @brief Start the axis controller
  void start() {
    boost::asio::co_spawn(Strand, runTimer(), boost::asio::detached);
  }
};

struct SkywatcherAxes {
private:
  SkywatcherAxis Axis1;
  SkywatcherAxis Axis2;

public:
  SkywatcherAxis &getAxis(skywatcher::MountAxis Axis) {
    return Axis == skywatcher::MA_1 ? Axis1 : Axis2;
  }
  const SkywatcherAxis &getAxis(skywatcher::MountAxis Axis) const {
    return getAxis(Axis);
  }
  const SkywatcherAxis &operator[](skywatcher::MountAxis Axis) const {
    return getAxis(Axis);
  }
  SkywatcherAxis &operator[](skywatcher::MountAxis Axis) {
    return getAxis(Axis);
  }
};

struct SkywatcherMount {
  SkywatcherAxes Axes;
};
