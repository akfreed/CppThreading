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

#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <array>

namespace strapper { namespace mt {

class CyclicBarrier
{
public:
    explicit CyclicBarrier(unsigned numParticipants);

    void Sync();

private:
    std::mutex m_mutex;
    std::condition_variable m_cv;
    unsigned m_numParticipants = std::thread::hardware_concurrency();
    std::array<unsigned, 2> m_count{ 0, 0 };
    unsigned m_index = 0;
};

} } // strapper::mt
