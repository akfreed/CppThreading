// ==================================================================
// Copyright 2016-2022 Alexander K. Freed
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

#include <strapper/mt/CyclicBarrier.h>

// Behavior is undefined if an instance is destructed while other treads are in the sync function.
// todo: add timeout for sync

namespace strapper { namespace mt {

CyclicBarrier::CyclicBarrier(unsigned numParticipants)
    : m_numParticipants(numParticipants)
{ }

void CyclicBarrier::Sync()
{
    std::unique_lock<std::mutex> lock(m_mutex);

    unsigned& count = m_count.at(m_index);
    ++count;

    if (count < m_numParticipants)
        m_cv.wait(lock, [&count]() { return count == 0; });
    else
    {
        // Flip index.
        m_index ^= 0x1;

        count = 0;
        m_cv.notify_all();
    }
}

} } // strapper::mt
