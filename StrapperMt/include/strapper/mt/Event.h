// ==================================================================
// Copyright 2022 Alexander K. Freed
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ==================================================================

#pragma once

#include <mutex>
#include <future>
#include <chrono>

namespace strapper { namespace mt {

template <typename R>
bool FutureIsReady(std::future<R> const& f)
{
    // throw if !f.valid()
    return f.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
}

template <typename R>
bool FutureIsReady(std::shared_future<R> const& f)
{
    // throw if !f.valid()
    return f.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
}

class Event
{
public:
    Event();

    bool IsSet() const;

    void Set();
    void Clear();
    void Wait();

private:
    mutable std::mutex m_mutex;
    bool m_state = false;
    std::promise<void> m_promise;
    std::shared_future<void> m_future;
};

} }  // strapper::mt
