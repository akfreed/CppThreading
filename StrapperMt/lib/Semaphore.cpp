// ==================================================================
// Copyright 2014-2022 Alexander K. Freed
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

#include <strapper/mt/Semaphore.h>

// Behavior is undefined if an instance is destructed while other treads are in the up or down functions.
// todo: add multi-count down
// todo: add timeout for down

namespace strapper { namespace mt {

Semaphore::Semaphore(int initialCount /* = 0 */)
    : m_count(initialCount)
{ }

//! Block if count is 0 or less.
void Semaphore::Down()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cv.wait(lock, [this]() { return m_count > 0; });
    --m_count;
}

void Semaphore::Up()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    ++m_count;
    if (m_count > 0)
        m_cv.notify_one();
}

} } // strapper::mt
