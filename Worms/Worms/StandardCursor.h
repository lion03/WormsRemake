/**
 \file	StandardCursor.h

 \brief	Declares the standard cursor class.
 */

#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#ifdef SFML_SYSTEM_WINDOWS
#include <windows.h>
#elif defined(SFML_SYSTEM_LINUX)
#include <X11/cursorfont.h>
#include <X11/Xlib.h>
#else
#error This OS is not yet supported by the cursor library.
#endif

/**
 \brief	Standard cursor.
 */

class StandardCursor
{
private:
#ifdef SFML_SYSTEM_WINDOWS

	HCURSOR Cursor; /*Type of the Cursor with Windows*/ ///< Handle of the cursor

#else

	XID Cursor; ///< The cursor
	Display* display;   ///< The display

#endif
public:

	/**
	 \brief	Values that represent TYPE.
	 */

	enum TYPE{ WAIT, TEXT, NORMAL, HAND , PIC };

	/**
	 \brief	Initializes a new instance of the StandardCursor class.
	
	 \param	t   	The const TYPE to process.
	 \param	path	(optional) full pathname of the file.
	 */

	StandardCursor(const TYPE t, const std::string & path = "" );

	/**
	 \brief	Sets the given a window handle.
	
	 \param	aWindowHandle	The window handle to set.
	 */

	void set(const sf::WindowHandle& aWindowHandle) const;

	/**
	 \brief	Finalizes an instance of the StandardCursor class.
	 */

	~StandardCursor();
};

/**
// End of StandardCursor.h
 */

