#include <Windows.h>
#include <iostream>

#include "Clipboard.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;

Clipboard::Clipboard()
{
}


Clipboard::~Clipboard()
{
}

void Clipboard::copy_to_clipboard(string &str)
{
	HWND handle = GetConsoleWindow();

    // attempt to open clipboard
	if (!OpenClipboard(handle))
	{
		cerr << "Clipboard failed to open" << endl;
    }
    else // successful
    {

        // attempt to empty clipboard
		if (!EmptyClipboard())
		{
			cerr << "Failed to empty clipboard" << endl;
        }
        else // successful
        {

            // attempt to allocate global memory for clipboard
			HGLOBAL text = GlobalAlloc(GMEM_MOVEABLE, str.size() + 1);
			if (!text)
			{
				cerr << "global memory allocation failed" << endl;
            }
            else // successful
            {

				memcpy(GlobalLock(text), str.c_str(), str.size() + 1);
				GlobalUnlock(text);

                // attempt to copy contents of memory to clipboard
                if (!SetClipboardData(CF_TEXT, text))
				{
					cerr << "failed to set clipboard data" << endl;
                }
                else // successful
				{
					cout << "successfully set clipboard data" << endl;
                }

				GlobalFree(text);
			}
		}

        // attempt to close clipboard
		if (!CloseClipboard())
		{
			cerr << "failed to close clipboard" << endl;
		}
        else // successful
		{
			cout << "successfully closed clipbaord after opening" << endl;
		}
	}
}
