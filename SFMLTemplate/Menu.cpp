#include "Menu.h"

/**
Default constructor
*/
Menu::Menu(sf::Window* window, std::string uniqueName)
{
  this->isDisplayed = false;
  this->itemActivated = uniqueName;
  this->topName = uniqueName;
  this->window = window;
  setupFonts();
}

/**
Destructor
*/
Menu::~Menu()
{
  glDeleteLists(charListMenu, 96);
}

/**
Adds menu item to this menu collection.
*/
bool Menu::addMenuItem(Menu::MenuItem menuItem)
{
  menuItems.push_back(menuItem);
  return true;
}

/**
Draws button via OpenGL primitives.
*/
void Menu::buttonBox(sf::Vector2f position, sf::Vector2f size, MenuColor baseColor, GLuint buttonID)
{
  // Enable texture
  glEnable(GL_TEXTURE_2D);
  glPushMatrix();

  if (buttonID < 999)
  {
    glBindTexture(GL_TEXTURE_2D, texture_handle[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 
      menuItems.at(buttonID).image->getSize().x, 
      menuItems.at(buttonID).image->getSize().y, 
      0, GL_RGBA, GL_UNSIGNED_BYTE, 
      menuItems.at(buttonID).image->getPixelsPtr());
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Draw background for the menu/button
    glColor4f(baseColor.r, baseColor.g, baseColor.b, baseColor.a);
    glBegin(GL_QUADS);
	//glTexCoord2f(0.0f, 1.0f); glVertex2d(position.x, position.y);
	//glTexCoord2f(0.0f, 0.0f); glVertex2d(position.x, position.y + size.y);
	//glTexCoord2f(1.0f, 0.0f); glVertex2d(position.x + size.x, position.y + size.y);
	//glTexCoord2f(1.0f, 1.0f); glVertex2d(position.x + size.x, position.y);

	glTexCoord2f(0.0f, 0.0f); glVertex2d(position.x, position.y);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(position.x, position.y + size.y);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(position.x + size.x, position.y + size.y);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(position.x + size.x, position.y);
    glEnd();
  }
  else
  {
    glColor4f(baseColor.r, baseColor.g, baseColor.b, baseColor.a);
    glBegin(GL_QUADS);
    glVertex2d(position.x, position.y);
    glVertex2d(position.x, position.y + size.y);
    glVertex2d(position.x + size.x, position.y + size.y);
    glVertex2d(position.x + size.x, position.y);
    glEnd();
  }

  // Draw border around the menu/button
  glColor4f(abs(baseColor.r - 0.2f), abs(baseColor.g - 0.2f), abs(baseColor.b - 0.2f), abs(baseColor.a - 0.2f));
  glLineWidth(5);
  glBegin(GL_LINE_LOOP);
  glVertex2d(position.x, position.y);
  glVertex2d(position.x, position.y + size.y);
  glVertex2d(position.x + size.x, position.y + size.y);
  glVertex2d(position.x + size.x, position.y);
  glEnd();
  
  // Disable texture
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

/**
Displays Menu on the screen as overlay on top of another Perspective view
*/
void Menu::display()
{
  if (isDisplayed)
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

    // Draw background box with border around complete menu
    buttonBox(menuPosition, menuSize, colorBackDefault, 1000);

    unsigned counter = 0; // button counter

    // Draw box with border for each visible menu button
    for(unsigned i = 0; i < menuItems.size(); i++)
    {
      if (menuItems.at(i)._topMenuName == itemActivated)
      {
        // Draw button
        buttonBox(
          sf::Vector2f(menuPosition.x, menuButtonSize.y * counter + menuPosition.y), 
          menuButtonSize, 
          menuItems.at(i).colorDefaultBack,
          i
        );

        // Add text to the button
        std::string text = menuItems.at(i).text;
        sf::Vector2i textSize = measureString(text, hFontMenu);

        textToScreen(
          hFontMenu, 
          charListMenu, 
          sf::Vector3f(
            menuPosition.x + (menuButtonSize.x - textSize.x) / 2, 
            menuPosition.y + menuButtonSize.y * (counter + 1) / 2 + textSize.y * counter, 
            200.0f), 
          colorTextDefault,
          "%s", text.c_str()
        );

        // Icnrement button counter
        counter++;
      }
    }

    //# Item Activated will tell which menus need to be displayed i.e. display all submenus who's container is itemActivated

    // # Iterate over map items and display items for top name menu
    // # if itemActivated != topName iterate over map items and display items under the top name menu
    // # if itemActivated != any item under topName keep displaying sub items under these menus until reached itemActivated

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glFlush();

	  glLineWidth(2);
	  glDepthMask(GL_TRUE);
	  glEnable(GL_DEPTH_TEST);
	  glEnable(GL_LIGHTING);
  }
}

/**
Handles events invoked by hot keys and mouse clicks.
*/
void Menu::handle(sf::Window* window, sf::Event* events)
{
  // Only perform handling if menu is actually displayed
  if (isDisplayed)
  {
    // Display mouse cursor since menu is visible
    window->setMouseCursorVisible(true);

    while(window->pollEvent(*events))
    {
      // Check for keyboard buttons released
      if (events->type == sf::Event::KeyReleased)
      {
        sf::Keyboard::Key key = events->key.code;
        auto lookup = 
          std::find_if(menuItems.begin(), menuItems.end(), [key](const MenuItem menuItem) { return (menuItem.mnemonic == key); });
        if (lookup != menuItems.end())
        {
          //auto index = std::distance(menuItems.begin(), lookup);  // Get the index of the coresponding menu item
          
          // This item was activated
          itemActivated = lookup->name; // The item was activated via hot key
          isDisplayed = false;  // Since we are now handling event hide this menu
          
          // Hide mouse cursor since menu is no longer displayed
          window->setMouseCursorVisible(false);
        }
      }

      // Check for mouse buttons released
      if (events->type == sf::Event::MouseButtonReleased)
      {
        // Get button name if clicked
        std::string itemClicked =
          getItemClicked(
            sf::Mouse::getPosition().x - (window->getPosition().x + 8),     // 8 = window border
            sf::Mouse::getPosition().y - (window->getPosition().y + 28)    // 28 is the hight of titlebar
          );

        // Check if button name was returned
        if (itemClicked != "")
        {
          itemActivated = itemClicked;  // Set clicked button as activated
          isDisplayed = false;          // Hide menu
        }
      }
    }
  }
}

/**
Returns name of activated menu
*/
std::string Menu::getItemActivated()
{
  return this->itemActivated;
}

/**
Returns name of this top menu
*/
std::string Menu::getMenuName()
{
  return this->topName;
}

/**
Returns whether this menu is displayed or not.
*/
bool Menu::IsDisplayed()
{
  return isDisplayed;
}

/**
Returns size of the string based on the font used.
*/
sf::Vector2i Menu::measureString(std::string text, HFONT font)
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
std::wstring Menu::stringToWideString(const std::string& str)
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
Sets value of isDisplayed (used to determine wether this menu is displayed or not)
*/
void Menu::setIsDisplayed(bool isDisplayed)
{
  this->isDisplayed = isDisplayed;
}

/**
Set the value of itemActivated (used to determine which menu item was clicked or hotkeyed)
*/
void Menu::setItemActivated(std::string item)
{
  this->itemActivated = item;
}

/**
Sets the size for menu buttons.
*/
void Menu::setMenuButtonSize(sf::Vector2f buttonSize)
{
  this->menuButtonSize = buttonSize;
}

/**
Sets particular menu color to whatever value is specified.
*/
void Menu::setMenuColor(Menu::MenuColor color, Menu::MENU_COLOR colorType)
{
  switch (colorType)
  {
  case Menu::MENU_BACK_ACTIVE_COLOR:
    this->colorBackActive = color;
    break;
  case Menu::MENU_BACK_DEFAULT_COLOR:
    this->colorBackDefault = color;
    break;
  case Menu::MENU_TEXT_ACTIVE_COLOR:
    this->colorTextActive = color;
    break;
  case Menu::MENU_TEXT_DEFAULT_COLOR:
    this->colorTextDefault = color;
    break;
  }
}

/**
Sets the name for this menu.
*/
void Menu::setMenuName(std::string name)
{
  this->topName = name;
}

/**
Sets the position for this menu.
*/
void Menu::setMenuPosition(sf::Vector2f position)
{
  this->menuPosition = position;
}

/**
Sets the size of this menu.
*/
void Menu::setMenuSize(sf::Vector2f size)
{
  this->menuSize = size;
}

/**
Sets the style of this menu.
*/
void Menu::setMenuStyle(Menu::MENU_STYLE style)
{
  this->menuStyle = style;
}

/**
Creates fonts to use when displaying times/scores
*/
void Menu::setupFonts()
{
  hdc = wglGetCurrentDC();
  charListMenu = glGenLists(96);
  
  // Font for this menu
  hFontMenu = 
    CreateFont(FONT_SIZE_MENU_MAIN, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, 
    OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, TEXT(FONT_NAME_MENU_MAIN));

  // Font for items inside this menu
  hFontMenuItem = 
    CreateFont(FONT_SIZE_MENU_ITEM, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, 
    OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, TEXT(FONT_NAME_MENU_ITEM));
}

/**
Prints Menu text to the screen.
*/
void Menu::textToScreen(HFONT font, unsigned charList, sf::Vector3f pos, Menu::MenuColor color, const char *str, ...)
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

/**
Returns name of the button clicked or empty string if no button was clicked.
*/
std::string Menu::getItemClicked(float mouseX, float mouseY)
{
  // STEP 1 - Check if click was inside menu rectangle before checking for button clicks
  if (mouseX >= menuPosition.x && mouseX <= menuPosition.x + menuSize.x
    && mouseY >= menuPosition.y && mouseY <= menuPosition.y + menuSize.y)
  {
    for(unsigned i = 0; i < menuItems.size(); i++)
    {
      if (mouseY >= (menuButtonSize.y * i + menuPosition.y) && 
        mouseY <= (menuButtonSize.y * (i + 1) + menuPosition.y)) return menuItems.at(i).name;
    }
  }
  else
    return "";
}