// Fonts definitions
#define FONT_NAME_GM "Comic Sans MS"
#define FONT_SIZE_GM 28

// Public section font definitions
HDC hdc;
HFONT hFont;
unsigned int charList;

// Call this from game.cpp init to setup fonts for use with help function.  
setupFonts();

/**
Draws simulated window with background via OpenGL polygons/primitives.
*/
void GameManager::drawWindow(sf::Vector2f position, sf::Vector2f size, GMColor baseColor)
{
  // Draw background for the menu/button
  glColor4f(baseColor.r, baseColor.g, baseColor.b, baseColor.a);
  glBegin(GL_QUADS);
  glVertex2d(position.x, position.y);
  glVertex2d(position.x, position.y + size.y);
  glVertex2d(position.x + size.x, position.y + size.y);
  glVertex2d(position.x + size.x, position.y);
  glEnd();

  // Draw border around the menu/button
  glColor4f(abs(baseColor.r - 0.2f), abs(baseColor.g - 0.2f), abs(baseColor.b - 0.2f), abs(baseColor.a - 0.2f));
  glLineWidth(5);
  glBegin(GL_LINE_LOOP);
  glVertex2d(position.x, position.y);
  glVertex2d(position.x, position.y + size.y);
  glVertex2d(position.x + size.x, position.y + size.y);
  glVertex2d(position.x + size.x, position.y);
  glEnd();
}

/**
  Displays window with help information
*/
void GameManager::displayHelp()
{
  glDisable(GL_LIGHTING);
  glDepthMask(GL_FALSE);
  glDisable(GL_DEPTH_TEST);
  glViewport(0, 0, window->getSize().x, window->getSize().y);

  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0.0f, window->getSize().x, window->getSize().y, 0.0f, -1000.f, 10000.0f);

  glMatrixMode(GL_MODELVIEW);


  // Draw background for the text
  drawWindow(
    sf::Vector2f(50.0f, 50.0f), 
    sf::Vector2f(
      (window->getPosition().x + window->getSize().x - 50.0f), 
      (window->getPosition().y + window->getSize().y - 50.0f)
    ), 
    GMColor(0.0f, 0.0f, 0.0f, 1.0f));
  
  // Add lines of text to the window
  textToScreen(hFont, charList, sf::Vector3f(150.0f, 150.0f, 200.0f), GMColor(0.0f, 0.0f, 0.0f, 1.0f), "%s", "This is help...");
  textToScreen(hFont, charList, sf::Vector3f(150.0f, 200.0f, 200.0f), GMColor(0.0f, 0.0f, 0.0f, 1.0f), "%s", "...");
  textToScreen(hFont, charList, sf::Vector3f(150.0f, 250.0f, 200.0f), GMColor(0.0f, 0.0f, 0.0f, 1.0f), "%s", "and some more text...");

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  glFlush();
  glLineWidth(2);
  glDepthMask(GL_TRUE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
}

/**
Returns size of the string based on the font used.
*/
sf::Vector2i GameManager::measureString(std::string text, HFONT font)
{
  std::wstring stemp = stringToWideString(text);  // Convert 1 byte chars to 2 byte chars
  LPCWSTR lwtext = stemp.c_str();                 // Convert to long pointer to wide string
  SIZE size;                                      // Size structure to store returned size of the string
  SelectObject(hdc, font);                        // Select font
  
  // Call function that will give us the size of the text
  GetTextExtentPoint32(hdc, lwtext, text.size(), &size);
  
  // Disect and return string size as the sf::Vector2i
  return sf::Vector2i(size.cx, size.cy);
}

/**
Converts regular ascii string (std::string) to unicode string (std::wstring)
*/
std::wstring GameManager::stringToWideString(const std::string& str)
{
  int len;
  int slength = (int)str.length() + 1;
  len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), slength, 0, 0); 
  wchar_t* buf = new wchar_t[len];
  MultiByteToWideChar(CP_ACP, 0, str.c_str(), slength, buf, len);
  std::wstring r(buf);
  delete[] buf;
  return r;
}

/**
Creates fonts to use when displaying times/scores
*/
void GameManager::setupFonts()
{
  hdc = wglGetCurrentDC();
  charList = glGenLists(96);
  
  // Font for this menu
  hFont = 
    CreateFont(FONT_SIZE_GM, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, 
    OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, TEXT(FONT_NAME_GM));
}

/**
Displays text output on the screen.
*/
void GameManager::textToScreen(HFONT font, unsigned charList, sf::Vector3f pos, GameManager::GMColor color, const char *str, ...)
{
  //if(glIsList(charList) == GL_FALSE) return;

  SelectObject(hdc, font);
  wglUseFontBitmaps(hdc, 32, 96, charList);

	char text[256];
	va_list args;

	if (str == NULL)
		return;

	va_start(args, str);
  vsprintf_s(text, str, args);
	va_end(args);

	glPushMatrix();
  glColor4f(color.r, color.g, color.b, color.a);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -1.0f);
  glRasterPos3f(pos.x, pos.y, pos.z);

	glPushAttrib(GL_LIST_BIT);
	glListBase(charList - 32);
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib();
	glPopMatrix();
}