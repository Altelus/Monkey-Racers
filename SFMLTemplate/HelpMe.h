#ifndef _GAMESMITHS_HELPME_H_
#define _GAMESMITHS_HELPME_H_

// includes
#include "Engine.h"
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <Windows.h>

// Font constants
#define FONT_NAME_TEXT1 "Comic Sans MS" // Type of font 1
#define FONT_NAME_TEXT2 "Comic Sans MS" // Type of font 2
#define FONT_NAME_TEXT3 "Comic Sans MS" // Type of font 3
#define FONT_SIZE_TEXT1 40              // Size of font 1
#define FONT_SIZE_TEXT2 32              // Size of font 2
#define FONT_SIZE_TEXT3 26              // Size of font 3

// Position of text lines on the screen
#define TEXT_LINE_1_X 90.0f
#define TEXT_LINE_1_Y 100.0f
#define TEXT_LINE_2_X 90.0f
#define TEXT_LINE_2_Y 220.0f
#define TEXT_LINE_3_X 90.0f
#define TEXT_LINE_3_Y 280.0f
#define TEXT_LINE_4_X 90.0f
#define TEXT_LINE_4_Y 340.0f
#define TEXT_LINE_5_X 90.0f
#define TEXT_LINE_5_Y 400.0f
#define TEXT_LINE_6_X 90.0f
#define TEXT_LINE_6_Y 460.0f
#define TEXT_LINE_7_X 90.0f
#define TEXT_LINE_7_Y 520.0f
#define TEXT_LINE_8_X 90.0f
#define TEXT_LINE_8_Y 580.0f
#define TEXT_LINE_9_X 90.0f
#define TEXT_LINE_9_Y 640.0f

class HelpMe
{
public:

  enum HELP_MODE
  {
    HELP,
    INTRO,
    TUTORIAL
  };

  HelpMe(sf::Window*);
  ~HelpMe(void);

  void displayHelp(HELP_MODE);
  sf::Vector2i measureString(std::string, HFONT);
  bool getIsDisplayed();
  void setIsDisplayed(bool);
  void setupFonts();
  void setupView();
  std::wstring stringToWideString(const std::string&);
  void textToScreen(HFONT, unsigned int, sf::Vector3f, sf::Color, const char*, ...);

private:

  // Game window and game state
  sf::Window* window;           // Contains reference to window
  
  // Fonts
  HDC hdc;                      // Device context
  HFONT hFontText1;             // Font used to display text 1
  HFONT hFontText2;             // Font used to display text 2
  HFONT hFontText3;             // Font used to display text 3
  unsigned int charListText1;   // Font list for text 1
  unsigned int charListText2;   // Font list for text 2
  unsigned int charListText3;   // Font list for text 3
  sf::Color colorText3;         // Color for font 1
  sf::Color colorText2;         // Color for font 2
  sf::Color colorText1;         // Color for font 3

  bool isDisplayed;             // Is help window displayed or not?

};

#endif