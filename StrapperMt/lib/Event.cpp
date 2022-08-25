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

#include <strapper/mt/Event.h>

namespace strapper { namespace mt {

Event::Event()
    : m_future(m_promise.get_future())
{ }

bool Event::IsSet() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return FutureIsReady(m_future);
}

void Event::Set()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!FutureIsReady(m_future))
        m_promise.set_value();
}

void Event::Clear()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_promise = std::promise<void>();
    m_future = m_promise.get_future();
}

void Event::Wait()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    std::shared_future<void> local = m_future;
    lock.unlock();

    local.wait();
}

} }  // strapper::mt
