/**
 \file	StandardCursor.cpp

 \brief	Implements the standard cursor class.
 */

#include "StandardCursor.h"


#ifdef SFML_SYSTEM_WINDOWS

/**
 \brief	Initializes a new instance of the StandardCursor class.

 \param	t   	The const StandardCursor::TYPE to process.
 \param	path	Full pathname of the file.
 */

StandardCursor::StandardCursor(const StandardCursor::TYPE t, const std::string & path )
{
	switch(t)
	{
	case StandardCursor::WAIT :
		Cursor = LoadCursor(NULL, IDC_WAIT);
		break;
	case StandardCursor::HAND :
		Cursor = LoadCursor(NULL, IDC_HAND);
		break;
	case StandardCursor::NORMAL :
		Cursor = LoadCursor(NULL, IDC_ARROW);
		break;
	case StandardCursor::TEXT :
		Cursor = LoadCursor(NULL, IDC_IBEAM);
		break;
	case StandardCursor::PIC:
		Cursor = LoadCursorFromFile(LPCWSTR(L"Cursor.cur"));
		break;
		//For more cursor options on Windows go here:
		// http://msdn.microsoft.com/en-us/library/ms648391%28v=vs.85%29.aspx
	}
}

/**
 \brief	Sets the given a window handle.

 \param	aWindowHandle	The window handle to set.
 */

void StandardCursor::set(const sf::WindowHandle& aWindowHandle) const
{
	SetClassLongPtr(aWindowHandle, GCLP_HCURSOR, reinterpret_cast<LONG_PTR>(Cursor));
}

/**
 \brief	Finalizes an instance of the StandardCursor class.
 */

StandardCursor::~StandardCursor()
{
	// Nothing to do for destructor :
	// no memory has been allocated (shared ressource principle)
}

#elif defined(SFML_SYSTEM_LINUX)

/**
 \brief	Initializes a new instance of the StandardCursor class.

 \param	t	The const sf::StandardCursor::TYPE to process.
 */

sf::StandardCursor::StandardCursor(const sf::StandardCursor::TYPE t)
{
	display = XOpenDisplay(NULL);

	switch(t)
	{
	case sf::StandardCursor::WAIT:
		Cursor = XCreateFontCursor(display, XC_watch);
		break;
	case sf::StandardCursor::HAND:
		Cursor = XCreateFontCursor(display, XC_hand1);
		break;
	case sf::StandardCursor::NORMAL:
		Cursor = XCreateFontCursor(display, XC_left_ptr);
		break;
	case sf::StandardCursor::TEXT:
		Cursor = XCreateFontCursor(display, XC_xterm);
		break;
		// For more cursor options on Linux go here:
		// http://www.tronche.com/gui/x/xlib/appendix/b/
	}
}

/**
 \brief	Sets the given a window handle.

 \param	aWindowHandle	The window handle to set.
 */

void sf::StandardCursor::set(const sf::WindowHandle& aWindowHandle) const
{
	XDefineCursor(display, aWindowHandle, Cursor);
	XFlush(display);
}

/**
 \brief	Finalizes an instance of the StandardCursor class.
 */

sf::StandardCursor::~StandardCursor()
{
	XFreeCursor(display, Cursor);
	delete display;
	display = NULL;
}

#else
#error This OS is not yet supported by the cursor library.
#endif

/**
// End of StandardCursor.cpp
 */

