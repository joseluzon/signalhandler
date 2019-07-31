// code-licenser auto-generated license header

// Copyright (C) 2019 Jose Luzón Martín
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <stdexcept>
#include <cstdio>
#include <execinfo.h>
#include <csignal>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <ctime>

namespace jluzoncpp {
namespace signalhandler {

class SIGHandler : public std::runtime_error
{
public:
    SIGHandler(const std::string& arg) : std::runtime_error(arg) {}
    virtual ~SIGHandler() {}

    virtual void handle() = 0;
};

class DummySIGSEGVHandler : public SIGHandler
{
public:
    DummySIGSEGVHandler() : SIGHandler("SIGSEGV Error") {}
    virtual ~DummySIGSEGVHandler() override {}

    virtual void handle() override {}
};

/**
 * @brief CSignalHandler
 */
template<class SIGHandler>
class SignalHandler
{
public:
    static void signalHandler(int /*numSig*/)
    {
        SIGHandler e;
        e.handle();

        void* back_stack [50];
        char **back_str = nullptr;

        size_t size = backtrace(back_stack, 50);

        std::time_t curTime = std::time(nullptr);

        std::ofstream f;

        f.open ("crash.log", std::ofstream::out | std::ofstream::app);

        f << "************************" << std::endl;
        f << std::asctime(std::localtime(&curTime)) << e.what() << std::endl;

        back_str = backtrace_symbols(back_stack, size);
        if (back_str != nullptr)
        {
            for (size_t j = 0; j < size; j++)
                 f << back_str[j] << std::endl;
        }
        f << std::endl;

        f.close();

        free(back_str);

        exit(EXIT_FAILURE);
    }
};
    
} // signalhandler    
} // jluzoncpp
