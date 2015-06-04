#ifndef _GAMESMITHS_MENU_H_
#define _GAMESMITHS_MENU_H_

//SFML includes
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "glext.h"

// Other includes
#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <Windows.h>

// Font constants
#define FONT_NAME_MENU_MAIN "Comic Sans MS"
#define FONT_NAME_MENU_ITEM "Comic Sans MS"
#define FONT_SIZE_MENU_MAIN 28                // Size of menu strip or top level menu font
#define FONT_SIZE_MENU_ITEM 28                // Size of menu item font

// Timer constants
#define MILLISECONDS_IN_MINUTE 60000          // # of milliseconds in one minute
#define MILLISECONDS_IN_SECOND 1000           // # of milliseconds in one second
#define TIMER_MENU_DISPLAY_DELAY 250          // Delay in milliseconds before menu is displayed
#define TIMER_MENU_CLICK_DELAY 250            // Delay in milliseconds before menu responds to click

class Menu
{
public:

  // Enumeration for menu styles
  enum MENU_STYLE
  {
    MENU_FIXED_WINDOW,
    MENU_POPUP_WINDOW
  };

  // Enumeration for menu colors
  enum MENU_COLOR
  {
    MENU_BACK_ACTIVE_COLOR,
    MENU_BACK_DEFAULT_COLOR,
    MENU_TEXT_ACTIVE_COLOR,
    MENU_TEXT_DEFAULT_COLOR,
  };

  // MenuColor data structure (use for text, strip color, and background)
  struct MenuColor
  {
    float r, g, b, a;
    MenuColor() {}
    MenuColor(float rc, float gc, float bc, float ac) :  
    r(rc), g(gc), b(bc), a(ac) {}
  };

  // MenuItem data structure
  struct MenuItem
  {
    std::string _topMenuName;
    MenuColor colorActiveBack;
    MenuColor colorDefaultBack;
    MenuColor colorOnHover;
    bool isContainer;    
    bool isDisplayed;
    sf::Keyboard::Key mnemonic;
    std::string name;
    std::string text;
    sf::Image* image;
    //void (*call_back_func)(sf::Window*);
    
    MenuItem() 
    { 
      isDisplayed = false; 
    }
    
    MenuItem(
      std::string containerName, bool isSubMenu, sf::Keyboard::Key hotKey, std::string uniqueName, std::string caption, sf::Image* imageBack) : 
    _topMenuName(containerName), isContainer(isSubMenu), mnemonic(hotKey), name(uniqueName), text(caption), image(imageBack)
    { 
      isDisplayed = false; 
    }
    
    MenuItem(std::string containerName, bool isSubMenu, sf::Keyboard::Key hotKey, std::string uniqueName, std::string caption,
      MenuColor backColorDefault, MenuColor backColorOnActived, MenuColor backColorOnHover, sf::Image* imageBack) : 
    _topMenuName(containerName), isContainer(isSubMenu), mnemonic(hotKey), name(uniqueName), text(caption), 
      colorDefaultBack(backColorDefault), colorActiveBack(backColorOnActived), colorOnHover(backColorOnHover), image(imageBack) 
    { 
      isDisplayed = false; 
    }
  };

  Menu(sf::Window*, std::string);             // Menu constructor
  ~Menu();                                    // Menu destructor

  bool addMenuItem(MenuItem);                 // Adds menu item to this menu
  void buttonBox (sf::Vector2f, sf::Vector2f, 
            MenuColor, GLuint);               // Creates filled rectangle with border representing menu button
  void display();                             // Displays menu as an overlay on the existing screen
  void handle(sf::Window*, sf::Event*);       // Handles events invoked by keyboard keys and mouse clicks
  std::string getItemActivated();             // Returns name of the button activated through hot key or mouse click
  std::string getMenuName();                  // Returns name of this top menu
  std::string getItemClicked(float, float);   // Returns name of the button if button was clicked on, empty string if no button is clicked
  bool IsDisplayed();                         // Returns true if the menu is currently displayed on the screen
  void setIsDisplayed(bool);                  // Sets value of isDisplayed
  sf::Vector2i measureString(std::string, HFONT); // Returns size of the string in pixels (x - width, y - height)
  void setItemActivated(std::string);         // Sets the value of the button activated through hot key or mouse click
  void setMenuButtonSize(sf::Vector2f);       // Sets the size of menu button
  void setMenuColor(MenuColor, MENU_COLOR);   // Changes particular menu color
  void setMenuPosition(sf::Vector2f);         // Sets position of the menu inside the window
  void setMenuSize(sf::Vector2f);             // Sets size of the menu
  void setMenuStyle(MENU_STYLE);              // Applies menu style to this menu
  void setMenuName(std::string name);         // Sets name for this menu (topName)
  void setupFonts();                          // Creates fonts to be used for menu display
  std::wstring stringToWideString
    (const std::string&);                     // Converst std::string to std::wstring
  void textToScreen(                          // Prints the rasterized text to the screen
    HFONT,
    unsigned int,
    sf::Vector3f,
    MenuColor,
    const char*, 
    ...
  );

private:

  // Menu host window, container, and style
  std::string topName;                        // This is main level menu and name must be unique
  sf::Window* window;                         // Contains reference to window hosting menu
  std::vector<MenuItem> menuItems;            // list of menu items with their subitems
  MENU_STYLE menuStyle;                       // Tracks this menu style
  std::string itemActivated;                  // By default points to this menu, but if submenu is clicked or item then it points to that item
  sf::Vector2f menuPosition;                  // Position of the menu inside the window
  sf::Vector2f menuSize;                      // Size of the menu inside the window (x = width, y = height)
  sf::Vector2f menuButtonSize;                // Size of the menu button inside menu
  bool isDisplayed;                           // Tracks if the menu is displayed on the screen
  
  // Fonts
  HDC hdc;                                    // Device context
  HFONT hFontMenu;                            // Font used to display main menu
  HFONT hFontMenuItem;                        // Font used to display menu items
  unsigned int charListMenu;                  // Font list for menus
  MenuColor colorBackActive;
  MenuColor colorBackDefault;
  MenuColor colorTextActive;                  // Text color for active (clicked) menu items
  MenuColor colorTextDefault;                 // Text color for static menu items

  // Button texture
  GLuint texture_handle[2];                       // Handles for texture
};

#endif
