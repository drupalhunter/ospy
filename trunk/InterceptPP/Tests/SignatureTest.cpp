//
// Copyright (c) 2007 Ole Andr� Vadla Ravn�s <oleavr@gmail.com>
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//

#include <InterceptPP/InterceptPP.h>
#include <InterceptPP/ConsoleLogger.h>
#include <iostream>

using namespace std;
using namespace InterceptPP;

int main(int argc, char *argv[])
{
    Initialize();
    SetLogger(new Logging::ConsoleLogger());

    unsigned char buf[] = "\x6A\x20"
                          "\x68\xD8\xD2\xCB\x77"
                          "\xE8\x23\x8C\x01\x00";

    OString s1 =
        "6A 20"             // push 20h
        "68 D8 D2 CB 77"    // push offset dword_77CBD2D8
        "E8 23 8C 01 00";   // call __SEH_prolog4
    Signature sig1(s1);

    OString s2 =
        "6A ??"             // push ??
        "68 ?? ?? ?? ??"    // push ?? ?? ?? ??
        "E8 ?? ?? ?? ??";   // call ?? ?? ?? ??
    Signature sig2(s2);

    OVector<void *>::Type matches = SignatureMatcher::Instance()->FindInRange(sig1, buf, sizeof(buf));
    cout << "sig1, matches.size() == " << matches.size() << endl;

    matches = SignatureMatcher::Instance()->FindInRange(sig2, buf, sizeof(buf));
    cout << "sig2, matches.size() == " << matches.size() << endl;

    cout << "success" << endl;
    OString str;
    cin >> str;

	return 0;
}

