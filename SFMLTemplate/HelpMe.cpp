#include "HelpMe.h"

/**
Default constructor
*/
HelpMe::HelpMe(sf::Window* window)
{
  this->window = window;
  setupFonts();                   // Create fonts to be used to display time/score/messages
}

/**
Destructor
*/
HelpMe::~HelpMe(void)
{
  // Cleanup
  glDeleteLists(charListText1, 96);
  glDeleteLists(charListText2, 96);
  glDeleteLists(charListText3, 96);
}

/**
Displays help text on the screen as overlay on top of another Perspective view
*/
void HelpMe::displayHelp(HelpMe::HELP_MODE helpMode)
{
  sf::Color tempColor;        // Temporary color for window border and timer text

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

  // Draw background for the help "window"
  glColor4f(0.255f, 0.412f, 0.882f, 1.0f);
  glBegin(GL_QUADS);
  glVertex2d(50.0f, 50.0f);
  glVertex2d(50.0f, window->getSize().y - 50.0f);
  glVertex2d(window->getSize().x - 50.0f, window->getSize().y - 50.0f);
  glVertex2d(window->getSize().x - 50.0f, 50.0f);
  glEnd();

  // Draw border around the "window"
  glColor4f(0.27f, 0.27f, 0.0f, 1.0f);
  glLineWidth(5);
  glBegin(GL_LINE_LOOP);
  glVertex2d(50.0f, 50.0f);
  glVertex2d(50.0f, window->getSize().y - 50.0f);
  glVertex2d(window->getSize().x - 50.0f, window->getSize().y - 50.0f);
  glVertex2d(window->getSize().x - 50.0f, 50.0f);
  glEnd();

  // Display some text
  if (helpMode == this->HELP)
  {
    textToScreen(hFontText1, charListText1, sf::Vector3f(TEXT_LINE_1_X, TEXT_LINE_1_Y, 0.0f), colorText1, "Monkey Racer %s", "Help");
    textToScreen(hFontText2, charListText2, sf::Vector3f(TEXT_LINE_2_X, TEXT_LINE_2_Y, 0.0f), colorText2, "%s", "Use Mouse/Keyboard to controll the character");
    textToScreen(hFontText2, charListText2, sf::Vector3f(TEXT_LINE_3_X, TEXT_LINE_3_Y, 0.0f), colorText2, "Mouse Move %s", "- Change camera viewing angle");
    textToScreen(hFontText2, charListText2, sf::Vector3f(TEXT_LINE_4_X, TEXT_LINE_4_Y, 0.0f), colorText2, "Keyboard W %s", "- Moves character forward");
    textToScreen(hFontText2, charListText2, sf::Vector3f(TEXT_LINE_5_X, TEXT_LINE_5_Y, 0.0f), colorText2, "Keyboard S %s", "- Moves character backward");
    textToScreen(hFontText2, charListText2, sf::Vector3f(TEXT_LINE_6_X, TEXT_LINE_6_Y, 0.0f), colorText2, "Keyboard A %s", "- Moves character left");
    textToScreen(hFontText2, charListText2, sf::Vector3f(TEXT_LINE_7_X, TEXT_LINE_7_Y, 0.0f), colorText2, "Keyboard D %s", "- Moves character right");
    textToScreen(hFontText3, charListText3, sf::Vector3f(TEXT_LINE_9_X, TEXT_LINE_9_Y, 0.0f), colorText3, "Mouse right click %s", "- Dismiss this window");
  }
  
  if (helpMode == this->INTRO)
  {
    textToScreen(
      hFontText2, charListText2, 
      sf::Vector3f(40.0f, 40.0f, 200.0f), colorText3,
      "Monkey Racer: %s", "Introduction..."
    );
  }
  
  if (helpMode == this->TUTORIAL)
  {
    textToScreen(hFontText1, charListText1, sf::Vector3f(TEXT_LINE_1_X, TEXT_LINE_1_Y, 0.0f), colorText1, "Monkey Racer %s", "Tutorial");
    textToScreen(hFontText2, charListText2, sf::Vector3f(TEXT_LINE_2_X, TEXT_LINE_2_Y, 0.0f), colorText2, "%s", "You are taking vacation on a remote island.");
    textToScreen(hFontText2, charListText2, sf::Vector3f(TEXT_LINE_3_X, TEXT_LINE_3_Y, 0.0f), colorText2, "%s", "Earthquake shakes the island and nearby volcano errupts.");
    textToScreen(hFontText2, charListText2, sf::Vector3f(TEXT_LINE_4_X, TEXT_LINE_4_Y, 0.0f), colorText2, "%s", "You left your boat in the harbour and need to reach it before lava reaches you");
    textToScreen(hFontText2, charListText2, sf::Vector3f(TEXT_LINE_5_X, TEXT_LINE_5_Y, 0.0f), colorText2, "%s", "Run fast and pickup coconuts and fruits along the way to get speed boost.");
    textToScreen(hFontText2, charListText2, sf::Vector3f(TEXT_LINE_6_X, TEXT_LINE_6_Y, 0.0f), colorText2, "%s", "However, be aware not to hit obstacles or step into oil patches that may slow you down.");
    textToScreen(hFontText3, charListText3, sf::Vector3f(TEXT_LINE_9_X, TEXT_LINE_9_Y, 0.0f), colorText3, "Mouse right click %s", "- Dismiss this window");
  }
    
  // Draw yellow border around the window
  glColor4f(tempColor.r, tempColor.g, tempColor.b, tempColor.a);
  glLineWidth(10);
  glBegin(GL_LINE_LOOP);
  glVertex2d(0, 0);
  glVertex2d(window->getSize().x, 0);
  glVertex2d(window->getSize().x, window->getSize().y);
  glVertex2d(0, window->getSize().y);
  glEnd();

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
sf::Vector2i HelpMe::measureString(std::string text, HFONT font)
{
  std::wstring stemp = stringToWideString(text);
  LPCWSTR lwtext = stemp.c_str();   // Convert to long pointer to wide string
  SIZE size;                        // Size structure to store size of the string
  SelectObject(hdc, font);          // Select font
  
  // Call function that will give us the size of the text
  GetTextExtentPoint32(hdc, lwtext, text.size(), &size);
  
  return sf::Vector2i(size.cx, size.cy);
}

bool HelpMe::getIsDisplayed()
{
  return isDisplayed;
}

void HelpMe::setIsDisplayed(bool isDisplayed)
{
  this->isDisplayed = isDisplayed; 
}

/**
Converts regular ascii string (std::string) to unicode string (std::wstring)
*/
std::wstring HelpMe::stringToWideString(const std::string& str)
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
void HelpMe::setupFonts()
{
  hdc = wglGetCurrentDC();

  charListText1 = glGenLists(96);
  charListText2 = glGenLists(96);
  charListText3 = glGenLists(96);

  colorText1 = sf::Color(1.0f, 0.5f, 0.0f, 1.0f);
  colorText2 = sf::Color(0.8f, 1.0f, 0.2f, 1.0f);
  colorText3 = sf::Color(0.0f, 1.0f, 1.0f, 1.0f);
  
  hFontText1 = 
    CreateFont(FONT_SIZE_TEXT1, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, 
    OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, TEXT(FONT_NAME_TEXT1));

  hFontText2 = 
    CreateFont(FONT_SIZE_TEXT2, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, 
    OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, TEXT(FONT_NAME_TEXT2));
  
  hFontText3 = 
    CreateFont(FONT_SIZE_TEXT3, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, 
    OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, TEXT(FONT_NAME_TEXT3));
}

/**
Setups view where text will display
*/
void HelpMe::setupView()
{

}

/**
Prints HelpMe text to the screen.
*/
void HelpMe::textToScreen(HFONT font, unsigned charList, sf::Vector3f pos, sf::Color color, const char *str, ...)
{
  if(glIsList(charList) == GL_FALSE) return;

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