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

#include <iostream>

#include "signalhandler.h"

int main()
{
    signal(SIGSEGV, jluzoncpp::signalhandler::SignalHandler<jluzoncpp::signalhandler::DummySIGSEGVHandler>::signalHandler);
    
    struct soo {
        int a;
        int b;
    };

    soo * ptr = nullptr;
    std::cout << ptr->a;

    exit(EXIT_SUCCESS);
}
