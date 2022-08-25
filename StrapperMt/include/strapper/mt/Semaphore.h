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

#pragma once

#include <mutex>
#include <condition_variable>

namespace strapper { namespace mt {

class Semaphore
{
public:
    explicit Semaphore(int initialCount = 0);

    void Down();
    void Up();

private:
    std::mutex m_mutex;
    std::condition_variable m_cv;
    int m_count = 0;
};

} } // strapper::mt
