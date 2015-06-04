#ifndef _GAMESMITHS_MENU_MANAGER_H_
#define _GAMESMITHS_MENU_MANAGER_H_

#include "Menu.h"
#include "sound.h"

namespace GameSmithsMenuManager
{
  // =================================================================================
  // Global type definitions
  // =================================================================================
  //typedef void (*func)(sf::Window*);                // function pointer type
  typedef void (*func)();                           // function pointer type
  typedef std::map<std::string, func> actions_map;  // Map of actions for menus

  // =================================================================================
  // States for the game - these control what is happening
  // =================================================================================
  enum ManagedGameState
  {
    HELP,
    EXIT,
    IDLE,
    NEW_GAME,
    PAUSE,
    RUN,
	  START,
    TUTORIAL
  };

  // =================================================================================
  // Global variables
  // =================================================================================
  sf::Window* hWindow;        // Pointer to a GameManager object
  ManagedGameState mgState;   // Holds current game state
  std::vector<Menu> menus;  // Collection of menus
  actions_map actions;      // Map of button names associated with corresponding button functions
  sf::Image img_start;
  sf::Image img_data;

  // =================================================================================
  // MenuManager functions prototypes
  // =================================================================================
  void CallFunction(const std::string&, sf::Window*);
  void CleanUp();
  void CreateMenus(sf::Window*);
  void DisplayMenus();
  bool IsAnyMenuDisplayed();
  ManagedGameState getGameState();
  void setGameState(ManagedGameState newState);

  // =================================================================================
  // Callback functions prototypes
  // =================================================================================
  void closeMenu();
  void displayHelp();
  void exitGame();
  void runNewGame();
  void runTutorial();
  void startScreen();

  // =================================================================================
  // =================================================================================
  // MENU MANAGER FUNCTION IMPLEMENTATIONS -- SCROLL DOWN FOR CALLBACK FUNCTION IMPLEMENTATIONS
  // =================================================================================
  // Returns current game state
  GameSmithsMenuManager::ManagedGameState getGameState()
  {
    return mgState;
  }

  // Changes current game state
  void setGameState(GameSmithsMenuManager::ManagedGameState newState)
  {
    mgState = newState;
  }

  /**
  Calls update method on displayed menu in order to handle window events i.e. key presses, mouse clicks, etc.
  Then it calls display method in order to display menu in response to handling performed in the update function.
  Returns true if the menu is currently displayed on the screen. Otherwise, it returns false.
  */
  bool ManageMenus(sf::Window* window, sf::Event* events, sound snd)
  {
	  if (mgState == START) 
	  {
		  if (events->key.code == sf::Keyboard::Escape) 
			  window->close();
		  else if (events->type == sf::Event::KeyReleased || 
			  events->type == sf::Event::MouseButtonReleased)
		  {
			  mgState = RUN;
			  menus.at(1).setIsDisplayed(false);
		  }
	  }

    // Check if any menu is already displayed
    if (IsAnyMenuDisplayed() != true)
    {

			
      // Check if key is pressed to invoke menu
      if (events->type == sf::Event::KeyReleased)
      {
        // Numeric 1 key pressed
        if (events->key.code == sf::Keyboard::Num1) 
          menus.at(0).setIsDisplayed(true);
        
        // Numeric 2 key pressed - this can be used to invoke second menu
        //else if (events->key.code == sf::Keyboard::Num2) menus.at(1).setIsDisplayed(true);


      }


      // Check for mouse click to invoke popup menu unless it is already displayed
      if (events->type == sf::Event::MouseButtonReleased)
      {
        // Check for mouse right click
        if (events->mouseButton.button == sf::Mouse::Right) 
        {
          mgState = IDLE;                     // Reset state
          menus.at(0).setIsDisplayed(true);   // Display menu
        }
      }
    }
    
    // Handle events in all menus (Menu.cpp handle method checks if menu is displayed)
    for(unsigned i = 0; i < menus.size(); i++) 
      menus.at(i).handle(window, events);

    // Check if any item is activated
    for(unsigned i = 0; i < menus.size(); i++) 
    {
		
      // Check if menu activated is not the top menu
      if (menus.at(i).getItemActivated() != menus.at(i).getMenuName())
      {
		  snd.playDawg();

        // Call function bound to the item activated
        CallFunction(menus.at(i).getItemActivated(), window);
        
        // Reset itemActivated
        menus.at(i).setItemActivated(menus.at(i).getMenuName());
      }
    }

    return IsAnyMenuDisplayed();
  }
  
  /**
  Iterates through map of actions to find menu associated with function to be executed.
  */
  void CallFunction(const std::string& funct, sf::Window* window)
  {
    //for(auto it = actions.cbegin(); it != actions.cend(); ++it)
    //{
    //  if (it->first == funct) (*(it->second))(window);
    //}

    actions_map::const_iterator iter = actions.find(funct);
    if (iter != actions.end())
    {
      //(*(iter->second))(window);    // Old way
      auto fn = iter->second;       // C++11 way
      (*fn)();
    }
  }

  /**
  Deletes menus collection to free the memory occupied by it.
  */
  void CleanUp()
  {
    if (menus.size() > 0) menus.clear();
  }

  /**
  Checks for any currently displayed menus and returns true if finds any.
  */
  bool IsAnyMenuDisplayed()
  {
    // Loop until any displayed menu is found
    for(unsigned i = 0; i < menus.size(); i++)
    {
      // If menu found return true
      if (menus.at(i).IsDisplayed() == true) return true;
    }
    // If no menus found return false
    return false;
  }
  
  /**
  Runs through menus collection and displays any menus that are supposed to be displayed.
  */
  void DisplayMenus()
  {
    // Main.cpp display method checks if menu is displayed
    for(unsigned i = 0; i < menus.size(); i++) menus.at(i).display();
  }

  /**
  Creates particular menus for window passed as parameter. 
  Window handle can be changed when calling DisplayMenus or ManageMenus method, so that menu can be displayed or handled by any window.
  */
  void CreateMenus(sf::Window* window)
  {
    hWindow = window;

    // Set game state to IDLE
    mgState = START;

    // #################################################################
    // #################### COMMON MENU SETTINGS #######################
    // These colors apply to background and text for top level menus
    Menu::MenuColor colorMenuBackDefault = Menu::MenuColor(0.8f, 1.0f, 0.0f, 1.0f);
    Menu::MenuColor colorMenuBackActive = Menu::MenuColor(0.8f, 1.0f, 0.0f, 1.0f);
    Menu::MenuColor colorMenuTextDefault = Menu::MenuColor(0.0f, 0.0f, 0.0f, 1.0f);
    Menu::MenuColor colorMenuTextActive = Menu::MenuColor(1.0f, 0.0f, 0.0f, 1.0f);

    // Colors for button background - these do not apply to top level menus
	Menu::MenuColor colorBackgroundDefault = Menu::MenuColor(0.8f, 1.0f, 0.0f, 1.0f);       // Background color before activated
	Menu::MenuColor colorBackgroundWhite = Menu::MenuColor(1.f, 1.0f, 1.0f, 1.0f);       // Background color before activated
    Menu::MenuColor colorBackgroundActivated = Menu::MenuColor(1.0f, 1.0f, 0.0f, 1.0f);     // Background color after activated
    Menu::MenuColor colorBackgroundHover = Menu::MenuColor(1.0f, 1.0f, 1.0f, 1.0f);         // Background color on hover (no hover atm)
    
    // Menu position, size, and button size (reuse variables for all menus) - this is position and size of first one
    sf::Vector2f size = sf::Vector2f(200.0f, 250.0f);
    sf::Vector2f position = sf::Vector2f((window->getSize().x - size.x) / 2, (window->getSize().y - size.y) / 2);
    sf::Vector2f buttonSize = sf::Vector2f(200.0f, 50.0f);
    
    // #################################################################
    // ################## TOP LEVEL GAME MENU START ####################
    // This is startup screen - one screen menu...
    Menu Startup(window, "startmenu");
	  Startup.setMenuButtonSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	  Startup.setIsDisplayed(true);

    // Create new game top menu and add it to menus collection
	  Menu mainGameMenu(window, "mainGameMenu");            // Create new menu
    mainGameMenu.setMenuStyle(Menu::MENU_FIXED_WINDOW);   // Apply style - This menu is fixed to one position in the window
    mainGameMenu.setMenuSize(size);                       // Set size of container (must be able to fit all buttons)
    mainGameMenu.setMenuPosition(position);               // Set position
    mainGameMenu.setMenuButtonSize(buttonSize);           // Size of individual button
    mainGameMenu.setMenuColor(colorMenuBackDefault, Menu::MENU_BACK_DEFAULT_COLOR); // Back color before click / activation
    mainGameMenu.setMenuColor(colorMenuBackActive, Menu::MENU_BACK_ACTIVE_COLOR);   // Back color after click / activation
    mainGameMenu.setMenuColor(colorMenuTextDefault, Menu::MENU_TEXT_DEFAULT_COLOR); // Text color before click / activation
    mainGameMenu.setMenuColor(colorMenuTextActive, Menu::MENU_TEXT_ACTIVE_COLOR);   // Text color after click / activation
    
    // Apply this image background to a button - overrides color setting
    img_start.loadFromFile("Resources/Textures/GUI/Start screen final.png");
    img_data.loadFromFile("Resources/Textures/Environment/grass.png");

    // ----- This is start screen
  	Menu::MenuItem startScreen("startmenu", false, sf::Keyboard::S, "startMenu", "",
		colorBackgroundWhite, colorMenuBackActive, colorBackgroundHover, &img_start);

    // ----- Run new game button
    Menu::MenuItem newGameMenu("mainGameMenu", false, sf::Keyboard::N, "newGameMenu", "[N]ew Game", 
      colorBackgroundDefault, colorBackgroundActivated, colorBackgroundHover, &img_data
    );
    // ----- Run tutorial game button
    Menu::MenuItem tutorialMenu("mainGameMenu", false, sf::Keyboard::T, "tutorialMenu", "[T]utorial", 
      colorBackgroundDefault, colorBackgroundActivated, colorBackgroundHover, &img_data
    );
    // ----- Help button
    Menu::MenuItem helpMenu("mainGameMenu", false, sf::Keyboard::H, "helpMenu", "[H]elp", 
      colorBackgroundDefault, colorBackgroundActivated, colorBackgroundHover, &img_data
    );
    // ----- Exit game button
    Menu::MenuItem exitGameMenu("mainGameMenu", false, sf::Keyboard::X, "exitGameMenu", "E[x]it Game", 
      colorBackgroundDefault, colorBackgroundActivated, colorBackgroundHover, &img_data
    );
    // ----- Close menu button
    Menu::MenuItem closeMenu("mainGameMenu", false, sf::Keyboard::C, "closeMenu", "[C]lose Menu", 
      colorBackgroundDefault, colorBackgroundActivated, colorBackgroundHover, &img_data
    );

    // Add all buttons to the menu
	Startup.addMenuItem(startScreen);
    
  mainGameMenu.addMenuItem(newGameMenu);
  mainGameMenu.addMenuItem(tutorialMenu);
  mainGameMenu.addMenuItem(helpMenu);
  mainGameMenu.addMenuItem(exitGameMenu);
  mainGameMenu.addMenuItem(closeMenu);

  menus.push_back(mainGameMenu);  // Add to menus collection
	
  menus.push_back(Startup);
    
    // ################## TOP LEVEL GAME MENU END ######################
    
    // #################################################################
    // ################## POPUP GAME MENU START ########################
    // Create new game top menu and add it to menus collection
    //Menu popupGameMenu(window, "popupMenu");                // Create new menu
    //popupGameMenu.setMenuStyle(Menu::MENU_POPUP_WINDOW);    // Apply style - This menu is popup i.e. displays at mouse position in the window
    //size = sf::Vector2f(200.0f, 200.0f);                    // Change size for this menu
    //popupGameMenu.setMenuSize(size);                        // Set menu size
    //position.y = (window->getSize().y - size.y) / 2;        // Calculate new position
    //popupGameMenu.setMenuPosition(position);                // Menu position
    //popupGameMenu.setMenuButtonSize(buttonSize);            // Size of individual button
    //popupGameMenu.setMenuColor(colorMenuBackDefault, Menu::MENU_BACK_DEFAULT_COLOR); // Back color before click / activation
    //popupGameMenu.setMenuColor(colorMenuBackActive, Menu::MENU_BACK_ACTIVE_COLOR);   // Back color after click / activation
    //popupGameMenu.setMenuColor(colorMenuTextDefault, Menu::MENU_TEXT_DEFAULT_COLOR); // Text color before click / activation
    //popupGameMenu.setMenuColor(colorMenuTextActive, Menu::MENU_TEXT_ACTIVE_COLOR);   // Text color after click / activation

    //// ----- New game button
    //Menu::MenuItem newGamePop = newGame;
    //newGamePop._topMenuName = "popupMenu";
    //
    //// Add all submenus and their items
    //popupGameMenu.addMenuItem(newGamePop);   // Reusing previously created newGameMenu item
    //menus.push_back(popupGameMenu); // Add to menus collection

    // ################## POPUP GAME MENU END ##########################
    // #################################################################


    // #################################################################
    // ================================================================================
    // ASSOCIATE ALL MENU BUTTONS WITH CALLBACK FUNCTIONS
    // ================================================================================
    actions.insert(std::make_pair("newGameMenu", &GameSmithsMenuManager::runNewGame));
    actions.insert(std::make_pair("tutorialMenu", &GameSmithsMenuManager::runTutorial));
    actions.insert(std::make_pair("helpMenu", &GameSmithsMenuManager::displayHelp));
    actions.insert(std::make_pair("exitGameMenu", &GameSmithsMenuManager::exitGame));
    actions.insert(std::make_pair("exitMenu", &GameSmithsMenuManager::closeMenu));
	  actions.insert(std::make_pair("startScreen", &GameSmithsMenuManager::startScreen));
    // ================================================================================
    // #################################################################
  }
    
  // =================================================================================
  // CALLBACK FUNCTIONS IMPLEMENTATIONS -- DON'T FORGET TO ADD MENUS IN ABOVE FUNCTION CreateMenus
  // =================================================================================
  /**
  Closes menu currently associated with the button.
  */ 
  void closeMenu()
  {
    mgState = IDLE;
  }

  /**
    Displays window with help information
  */
  void displayHelp()
  {
    mgState = HELP;
  }

  /**
    Closes window and exits current game
  */
  void exitGame()
  {
    mgState = EXIT;
  }

  /**
    Restarts the current game
  */
  void runNewGame()
  {
    mgState = NEW_GAME;
  }

  /**
    Opens window to allow saved game to be loaded
  */
  void runTutorial()
  {
    mgState = TUTORIAL;
  }

  void startScreen()
  {
	  mgState = START;
  }

};
#endif