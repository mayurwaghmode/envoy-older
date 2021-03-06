#include "source/common/http/http3_status_tracker_impl.h"

#include <chrono>
#include <functional>

namespace Envoy {
namespace Http {

namespace {

// Initially, HTTP/3 is be marked broken for 5 minutes.
const std::chrono::minutes DefaultExpirationTime{5};
// Cap the broken period at just under 1 day.
const int MaxConsecutiveBrokenCount = 8;
} // namespace

Http3StatusTrackerImpl::Http3StatusTrackerImpl(Event::Dispatcher& dispatcher)
    : expiration_timer_(dispatcher.createTimer([this]() -> void { onExpirationTimeout(); })) {}

bool Http3StatusTrackerImpl::isHttp3Broken() const { return state_ == State::Broken; }

bool Http3StatusTrackerImpl::isHttp3Confirmed() const { return state_ == State::Confirmed; }

void Http3StatusTrackerImpl::markHttp3Broken() {
  state_ = State::Broken;
  if (!expiration_timer_->enabled()) {
    std::chrono::minutes expiration_in_min =
        DefaultExpirationTime * (1 << consecutive_broken_count_);
    expiration_timer_->enableTimer(
        std::chrono::duration_cast<std::chrono::milliseconds>(expiration_in_min));
    if (consecutive_broken_count_ < MaxConsecutiveBrokenCount) {
      ++consecutive_broken_count_;
    }
  }
}

void Http3StatusTrackerImpl::markHttp3Confirmed() {
  state_ = State::Confirmed;
  consecutive_broken_count_ = 0;
  if (expiration_timer_->enabled()) {
    expiration_timer_->disableTimer();
  }
}

void Http3StatusTrackerImpl::onExpirationTimeout() {
  if (state_ != State::Broken) {
    return;
  }
  state_ = State::Pending;
}

} // namespace Http
} // namespace Envoy
