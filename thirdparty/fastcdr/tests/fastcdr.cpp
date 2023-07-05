// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

#include <fastcdr/Cdr.h>
#include <fastcdr/FastCdr.h>

#include <fastcdr/exceptions/BadParamException.h>
#include <fastcdr/exceptions/Exception.h>
#include <fastcdr/exceptions/NotEnoughMemoryException.h>

#include <stdio.h>
#include <limits>
#include <iostream>

#define EXPECT_LONG_DOUBLE_EQ(val1, val2) (val1 == val2)

using namespace eprosima::fastcdr;
using namespace ::exception;

#define BUFFER_LENGTH 2000
#define N_ARR_ELEMENTS 5


int main()
{
   char buffer[BUFFER_LENGTH];

    // Move assignment
   {
      eprosima::fastcdr::FastBuffer buffer1(buffer, BUFFER_LENGTH);
      buffer1.resize(1000);
      eprosima::fastcdr::FastBuffer buffer2 = std::move(buffer1);
   }

   // Move constructor
   {
      eprosima::fastcdr::FastBuffer buffer1(buffer, BUFFER_LENGTH);
      buffer1.resize(1000);
      eprosima::fastcdr::FastBuffer buffer2(std::move(buffer1));
   }
}
