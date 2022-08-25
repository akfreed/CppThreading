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

#include <strapper/mt/Semaphore.h>
#include <strapper/mt/CyclicBarrier.h>
#include <strapper/mt/Event.h>

#include <iostream>
#include <future>
#include <mutex>

using namespace strapper::mt;
using namespace std;

int main()
{
    mutex m;

    m.lock();

    auto l = [&m]() {
        m.unlock();
    };
    auto t1 = std::async(std::launch::async, l);
    //auto t2 = std::async(std::launch::async, l);
    //auto t3 = std::async(std::launch::async, l);
    //auto t4 = std::async(std::launch::async, l);

    std::cout << "Hello World" << std::endl;
    return EXIT_SUCCESS;
}
