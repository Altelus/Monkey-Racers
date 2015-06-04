#ifndef _GAMESMITHS_HUD_H_
#define _GAMESMITHS_HUD_H_

//SFML includes
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "glext.h"

// Other includes
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <Windows.h>

// Font constants
#define FONT_NAME_MESSAGE "Comic Sans MS"
#define FONT_NAME_SCORE "Comic Sans MS"
#define FONT_NAME_TIMER "Comic Sans MS"
#define FONT_SIZE_MESSAGE 72              // Size of messages font
#define FONT_SIZE_SCORE 48                // Size of score font
#define FONT_SIZE_TIMER 48                // Size of timer font

// Timer constants
#define MILLISECONDS_IN_MINUTE 60000      // # of milliseconds in one minute
#define MILLISECONDS_IN_SECOND 1000       // # of milliseconds in one second
#define TIMER_GOOD_TIME 60000             // time is at or above 60 seconds
#define TIMER_LOW_TIME 59999              // time is above 10 seconds and under 60 seconds
#define TIMER_BAD_TIME 10000              // time is at or below 10 seconds
#define TIMER_LEVEL_DISPLAY 3000          // Display level info for this many milliseconds for each level
#define TIMER_SHOW_MILLISECONDS false     // Instructs timer to show/hide milliseconds

class HUD
{
public:

  // Color data structure
  struct HUDTextColor
  {
    float r, g, b, a;
    HUDTextColor() {}
    HUDTextColor(float rc, float gc, float bc, float ac) :  
    r(rc), g(gc), b(bc), a(ac) {}
  };

  // Enumeration for game states
  enum HUD_GAME_STATE
  { 
    INIT = 0, 
    RUNNING = 1, 
    CLOSING = 2, 
    PAUSED = 3 
  };

  HUD(sf::Window*);             // Single parameter version of HUD constructor
  HUD(sf::Window*, int, INT64, long); // Overloaded version of HUD constructor
  ~HUD(void);                   // HUD destructor

  void display();               // Displays HUD as an overlay on the existing screen
  void update(bool);            // Updates current score, and timer for the level

  bool getIsCountdown();        // Returns whether the countdown state is ON or OFF
  bool getIsGameOver();         // Returns true if the game is finished (WON/LOST)
  INT64 getMsTime();            // Returns current time since the epoch
  long getScore();              // Return the score displayed in HUD
  INT64 getTimeLeft();

  std::string HUD::expandString
    (std::string textToExpand); // Expands string to a certain format "00:00:00"
  sf::Vector2i measureString
    (std::string, HFONT);       // Returns size of the string in pixels (x - width, y - height)

  void setIsCountdown(bool);    // Sets state for the countdown
  void setLevel(int);           // Sets the level
  void setLevelMax(int);        // Sets the maximum possible level
  void setScore(long);          // Changes the score in HUD
  void setTimeAllowed(INT64);   // Updates allowed time for the level to specified value (milliseconds)
  
  void setupFonts();            // Creates fonts to be used for time/score display
  std::wstring stringToWideString
    (const std::string&);       // Converst std::string to std::wstring
  void textToScreen(            // Prints the rasterized text to the screen
    HFONT,
    unsigned int,
    sf::Vector3f,
    HUDTextColor,
    const char*, 
    ...
  );

  std::string timeCounter();    // Returns string version of time countdown

  INT64 timeDiff(INT64, INT64); // Calculates the difference between two times in milliseconds
  
  HUD::HUD_GAME_STATE GetGameState() const { return gameState; }
  void SetGameState(HUD::HUD_GAME_STATE val) { gameState = val; }

private:

  // Game window and game state
  sf::Window* window;           // Contains reference to window hosting HUD
  HUD_GAME_STATE gameState;         // Tracks state for the game

  // Time tracking
  bool isCountdown;             // Should HUD display the countdown instead of time increase
  INT64 timeElapsed;            // Elapsed time since the game started running
  INT64 timeStart;              // Time (since epoch) when the level started running
  INT64 timeAllowed;            // Allowed time per game level (in microseconds)
  
  // Fonts
  HDC hdc;                      // Device context
  HFONT hFontMessage;           // Font used to display different messages
  HFONT hFontScore;             // Font used to display the score
  HFONT hFontTimer;             // Font used to display the timer  
  unsigned int charListMsgs;    // Font list for messages
  unsigned int charListScore;   // Font list for score
  unsigned int charListTimer;   // Font list for timer
  HUDTextColor colorScore;         // Text color for score
  HUDTextColor colorTimer;         // Default text color for the timer
  HUDTextColor colorTimerLow;      // Color for the timer when time is low
  HUDTextColor colorTimerCritical; // Color for the timer when time is critically low
  HUDTextColor colorMessage;       // Default text color for messages

  // Score and levels
  bool isGameOver;              // Is the game over
  int level;                    // Current level
  int maxLevel;                 // Maximum possible level
  long score;                   // Accumulated score since HUD started running

};

#endif