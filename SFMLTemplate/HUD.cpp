#include "HUD.h"

/**
Default constructor
*/
HUD::HUD(sf::Window* window)
{
  this->window = window;
  this->isCountdown = true;       // Timer is displayed as countdown (by default)
  this->level = 1;                // Set level to 1
  this->score = 0;                // Set score to 0
  this->timeElapsed = 0;          // Set elapsed time to 0
  this->timeAllowed = 120000;     // Time per level is 2 minutes by default (2[m] x 60[s] x 1000[ms] = 120000 ms)
  setupFonts();                   // Create fonts to be used to display time/score/messages
}

/**
Overloaded constructor
*/
HUD::HUD(sf::Window* window, int level, INT64 timeAllowedForLevel, long score)
{
  this->window = window;
  this->isCountdown = true;                 // By default count time down
  this->level = level;                      // Set new level
  this->score = score;                      // Set current score for this level
  this->timeElapsed = 0;                    // Reset elapsed time
  this->timeAllowed = timeAllowedForLevel;  // Set allowed time for this level
  setupFonts();                             // Create fonts to be used to display time, score, and messages
}

/**
Destructor
*/
HUD::~HUD(void)
{
  // Cleanup
  glDeleteLists(charListMsgs, 96);
  glDeleteLists(charListScore, 96);
  glDeleteLists(charListTimer, 96);
}

/**
Displays HUD on the screen as overlay on top of another Perspective view
*/
void HUD::display()
{
  HUDTextColor tempColor;        // Temporary color for window border and timer text

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

  // Check what game state are we in
  if (gameState == HUD::RUNNING)
  {
    // Display level for 3 seconds
    if (timeElapsed < TIMER_LEVEL_DISPLAY)
    {
      textToScreen(
        hFontMessage, charListScore, 
        sf::Vector3f((window->getSize().x - measureString("Level X", hFontMessage).x) / 2, window->getSize().y / 2, 0.0f), colorMessage,
        "Level: %d", level
      );
    }

    // Color of score/timer background strip
    HUDTextColor colr(0.4f, 0.4f, 0.4f, 0.8f);

    // Draw background for the score and timer
    glColor4f(colr.r, colr.g, colr.b, colr.a);
    glBegin(GL_QUADS);
    glVertex2d(0, 0);
    glVertex2d(0, measureString("Level X", hFontScore).y);
    glVertex2d(window->getSize().x, measureString("Level X", hFontScore).y);
    glVertex2d(window->getSize().x, 0);
    glEnd();

    // Draw border around the menu/button
    glColor4f(abs(colr.r - 0.2f), abs(colr.g - 0.2f), abs(colr.b - 0.2f), abs(colr.a - 0.2f));
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex2d(0, 0);
    glVertex2d(0, measureString("Level X", hFontScore).y);
    glVertex2d(window->getSize().x, measureString("Level X", hFontScore).y);
    glVertex2d(window->getSize().x, 0);
    glEnd();

    // Display score and the timer
    textToScreen(
      hFontScore, charListScore, 
      sf::Vector3f(40.0f, 40.0f, 200.0f), colorScore,
      "Score: %d", score
    );
    
    // Determine color of timer text
    if (timeDiff(timeAllowed, timeElapsed) <= TIMER_BAD_TIME) tempColor = colorTimerCritical;
    else if (timeDiff(timeAllowed, timeElapsed) <= TIMER_LOW_TIME) tempColor = colorTimerLow;
    else tempColor = colorTimer;

    // How the timer displays a time?
    std::string display = "";
    if (TIMER_SHOW_MILLISECONDS) display = "Time 00:00:000";
    else display = "Time 00:00";

    // Display timer
    textToScreen(
      hFontTimer, charListTimer, 
      sf::Vector3f(window->getSize().x - (measureString(display, hFontTimer).x + 40), 40.0f, 200.0f), tempColor,
      "Time: %s", timeCounter().c_str()
    );
  }
  else if (gameState == HUD::PAUSED)
  {
    // Display message "GAME PAUSED"
    textToScreen(
      hFontMessage, charListMsgs, 
      sf::Vector3f(100.0f, 100.0f, 200.0f), colorMessage,
      "GAME PAUSED"
    );
  }
  else if (gameState == HUD::CLOSING)
  {
    // Display message "GAME OVER"
    textToScreen(
      hFontMessage, charListMsgs, 
      sf::Vector3f(100.0f, 100.0f, 200.0f), colorMessage, 
      "GAME OVER"
    );
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
Updates values that should be displayed by the HUD on the screen
*/
void HUD::update(bool isLevelGoalReached)
{
  // Time elapsed between start and current time
  this->timeElapsed = timeDiff(this->timeStart, getMsTime());
  
  // Max-out time elapsed if the goal is reached
  if (isLevelGoalReached) this->timeElapsed = this->timeAllowed;

  // Is player running within allowed time
  if (this->timeElapsed <= this->timeAllowed)
  {
    // Did player reach the goal for the level?
    if (isLevelGoalReached)
    {
      // Was this the last level?
      if (this->level == this->maxLevel) 
      {
        this->isGameOver = true;
      }
      else  // Since this is not the last level, increment and setup next level
      {
        this->level++;                // Increment level
        isLevelGoalReached = false;   // Reset level goal reached
        this->gameState = HUD::INIT;        
      }
    }
  }
  // Was time exceeded, but goal not reached?
  else  // Restart the level
  {
    this->gameState = HUD::INIT;
  }

  // Need to change state to running if INIT is current game state
  if (gameState == HUD::INIT)
  {
    this->timeStart = getMsTime();          // Get new start time
    this->gameState = HUD::RUNNING;  // Change state to running
  }
}

/**
Returns the state of isCountdown i.e. whether time is counting down or up.
*/
bool HUD::getIsCountdown()
{
  return this->isCountdown;
}

/**
Returns the state of isGameOver i.e. whether the game is over or not.
*/
bool HUD::getIsGameOver()
{
  return this->isGameOver;
}

/** 
Returns current score displayed in the HUD.
*/
long HUD::getScore()
{
  return this->score;
}

/** 
Returns the amount of milliseconds elapsed since epoch time 
*/
INT64 HUD::getMsTime()
{
  FILETIME ft;
  LARGE_INTEGER li;
  GetSystemTimeAsFileTime(&ft);
  li.LowPart = ft.dwLowDateTime;
  li.HighPart = ft.dwHighDateTime;
  UINT64 ret = li.QuadPart;
  ret -= 116444736000000000LL; /* Convert from file time to epoch time. */
  ret /= 10000; /* From 100 nano seconds to 1 millisecond intervals */
  return ret;
}

/**
Sets the allowed time per level in milliseconds.
*/
void HUD::setTimeAllowed(INT64 timePerLevel)
{
  this->timeAllowed = timePerLevel;
}

/**
Sets the state of countdown in HUD.
*/
void HUD::setIsCountdown(bool isCountdown)
{
  this->isCountdown = isCountdown;
}

/**

*/
void HUD::setLevelMax(int maxLevel)
{
  this->maxLevel = maxLevel;
}

/**
Sets the state of countdown in HUD.
*/
void HUD::setScore(long newScore)
{
  this->score = newScore;
}

/**
Returns size of the string based on the font used.
*/
sf::Vector2i HUD::measureString(std::string text, HFONT font)
{
  std::wstring stemp = stringToWideString(text);
  LPCWSTR lwtext = stemp.c_str();   // Convert to long pointer to wide string
  SIZE size;                        // Size structure to store size of the string
  SelectObject(hdc, font);          // Select font
  
  // Call function that will give us the size of the text
  GetTextExtentPoint32(hdc, lwtext, text.size(), &size);
  
  return sf::Vector2i(size.cx, size.cy);
}

/**
Converts regular ascii string (std::string) to unicode string (std::wstring)
*/
std::wstring HUD::stringToWideString(const std::string& str)
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
void HUD::setupFonts()
{
  hdc = wglGetCurrentDC();

  // Character lists for different fonts
  charListMsgs = glGenLists(96);
  charListScore = glGenLists(96);
  charListTimer = glGenLists(96);

  // Colors for different fonts
  colorScore = HUDTextColor(0.0f, 1.0f, 1.0f, 1.0f);
  colorTimer = HUDTextColor(0.8f, 1.0f, 0.2f, 1.0f);
  colorTimerLow = HUDTextColor(1.0f, 0.5f, 0.0f, 1.0f);
  colorTimerCritical = HUDTextColor(1.0f, 0.0f, 0.0f, 1.0f);
  colorMessage = HUDTextColor(1.0f, 1.0f, 0.0f, 0.9f);

  // Score font
  hFontScore = 
    CreateFont(FONT_SIZE_SCORE, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, 
    OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, TEXT(FONT_NAME_SCORE));
  
  // Timer font
  hFontTimer = 
    CreateFont(FONT_SIZE_SCORE, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, 
    OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, TEXT(FONT_NAME_TIMER));

  // Messages font
  hFontMessage = 
    CreateFont(FONT_SIZE_MESSAGE, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, 
    OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, TEXT(FONT_NAME_MESSAGE));
}

/**
Prints HUD text to the screen.
*/
void HUD::textToScreen(HFONT font, unsigned charList, sf::Vector3f pos, HUD::HUDTextColor color, const char *str, ...)
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

/** 
Returns the difference between two times in milliseconds  
*/
INT64 HUD::timeDiff(INT64 time1, INT64 time2)
{
  // Return difference between times
  return (abs(time1 - time2));
}

/**
Returns timer value as formatted string.
*/
std::string HUD::timeCounter()
{
  std::stringstream ss;
  
  if (isCountdown)
  {
    int timeLeft = timeDiff(timeAllowed, timeElapsed);
    int timeMinutes = timeLeft / MILLISECONDS_IN_MINUTE;
    int timeSeconds = (timeLeft - timeMinutes * MILLISECONDS_IN_MINUTE) / MILLISECONDS_IN_SECOND;
    int timeMS = (timeLeft - (timeMinutes * MILLISECONDS_IN_MINUTE + timeSeconds * MILLISECONDS_IN_SECOND));
    
    // Create timer string with or without milliseconds
    if (TIMER_SHOW_MILLISECONDS)
      ss << timeMinutes << ":" << timeSeconds << ":" << timeMS;
    else
      ss << timeMinutes << ":" << timeSeconds;
  }
  else
  {
    int timeMinutes = timeElapsed / MILLISECONDS_IN_MINUTE;
    int timeSeconds = (timeElapsed - timeMinutes * MILLISECONDS_IN_MINUTE) / MILLISECONDS_IN_SECOND;
    int timeMS = (timeElapsed - (timeMinutes * MILLISECONDS_IN_MINUTE + timeSeconds * MILLISECONDS_IN_SECOND));

    // Create timer string with or without milliseconds
    if (TIMER_SHOW_MILLISECONDS)
      ss << timeMinutes << ":" << timeSeconds << ":" << timeMS;
    else
      ss << timeMinutes << ":" << timeSeconds;
  }

  std::string s = expandString(ss.str());
  
  return s;
}

/**
Adds leading characters to a string
*/
std::string HUD::expandString(std::string textToExpand)
{
  
  return textToExpand;
}

INT64 HUD::getTimeLeft()
{
	int timeLeft = timeDiff(timeAllowed, timeElapsed);
	int timeMinutes = timeLeft / MILLISECONDS_IN_MINUTE;
	int timeSeconds = (timeLeft - timeMinutes * MILLISECONDS_IN_MINUTE) / MILLISECONDS_IN_SECOND;

	return (timeMinutes*60)+timeSeconds;
}
