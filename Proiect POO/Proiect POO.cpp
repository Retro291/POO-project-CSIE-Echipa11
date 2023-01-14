#include <iostream>

#include "string"

#include "./meniu/IMeniu.h"
#include "./meniu/MeniuClient.h"
#include "./meniu/MeniuMagazin.h"

using namespace std;

int main() {
  DataBase::GetInstance().incarcaDatele();

  IMeniu* meniu = nullptr;

  string utilizator;
  string parola;



  cout << R"(                                                                                                                                                                                                     
     ___  ___   ___  ___  ___  ___  _____   ___   ___    ___                                         
    | _ \| _ \ / _ \|_ _|| __|/ __||_   _| | _ \ / _ \  / _ \                                        
    |  _/|   /| (_) || | | _|| (__   | |   |  _/| (_) || (_) |                                       
    |_|  |_|_\ \___/|___||___|\___|  |_|   |_|   \___/  \___/                                        
  __  __    _    ___    _    ____ ___  _  _   ___  _     ___  ___  _____  ___   ___   _  _  ___  ___ 
 |  \/  |  /_\  / __|  /_\  |_  /|_ _|| \| | | __|| |   | __|/ __||_   _|| _ \ / _ \ | \| ||_ _|/ __|
 | |\/| | / _ \| (_ | / _ \  / /  | | | .` | | _| | |__ | _|| (__   | |  |   /| (_) || .` | | || (__ 
 |_|  |_|/_/ \_\\___|/_/ \_\/___||___||_|\_| |___||____||___|\___|  |_|  |_|_\ \___/ |_|\_||___|\___|
                                                                                                     
                                                                                                                                                                                                                                                                                                                                                                                                                          
)" << endl;

  cout << R"(
                   __ _            __       __      _                                                 
  ____ ___  ___ _ / /(_)___ ___ _ / /_  ___/ /___  (_)                                                
 / __// -_)/ _ `// // //_ // _ `// __/ / _  // -_)_                                                   
/_/   \__/ \_,_//_//_/ /__/\_,_/ \__/  \_,_/ \__/(_)                                                  
   __         __              ___            __                           ____                        
  / /  ___ _ / /  ___  ___   / _ |  ___  ___/ /____ ___  ___  ___ _ ____ /  _/___  ___ _ ___  ___ _   
 / /__/ _ `// _ \/ -_)(_-<  / __ | / _ \/ _  // __// -_)/ -_)/ _ `//___/_/ / / _ \/ _ `// _ \/ _ `/   
/____/\_,_//_.__/\__//___/ /_/ |_|/_//_/\_,_//_/   \__/ \__/ \_,_/     /___/ \___/\_,_//_//_/\_,_/    
   __    _       _  __          _____            _                                                    
  / /   (_)___  (_)/ /_ ___ _  / ___/___   ____ (_)___  ___ _                                         
 / /__ / /(_-< / // __// _ `/ / /__ / _ \ / __// // _ \/ _ `/                                         
/____//_//___//_/ \__/ \_,_/  \___/ \___//_/  /_//_//_/\_,_/                                          
   ____                                 ___         __             __        ____ __            _     
  /  _/___   ___  ___  ___ ____ __ __  / _ \ ___   / /  ___  ____ / /_ ____ / __// /___   ____ (_)___ 
 _/ / / _ \ / _ \/ -_)(_-</ __// // / / , _// _ \ / _ \/ -_)/ __// __//___// _/ / // _ \ / __// // _ \
/___/ \___//_//_/\__//___/\__/ \_,_/ /_/|_| \___//_.__/\__//_/   \__/     /_/  /_/ \___//_/  /_//_//_/
   __  ___       __        _   ____ __        ___                 ____           __   _               
  /  |/  /___ _ / /_ ___  (_) / __// /_ ___  / _/___ _ ___  ____ /  _/__ __ ___ / /_ (_)___           
 / /|_/ // _ `// __// -_)/ / _\ \ / __// -_)/ _// _ `// _ \/___/_/ / / // /(_-</ __// // _ \          
/_/  /_/ \_,_/ \__/ \__//_/ /___/ \__/ \__//_/  \_,_//_//_/    /___/ \_,_//___/\__//_//_//_/          
   ____             _  __          __                           __  ___            _                  
  /  _/___   ___   (_)/ /_ ___ _  / /  ___ _ __ __ ____ ___ _  /  |/  /___ _ ____ (_)___ _            
 _/ / / _ \ / _ \ / // __// _ `/ / /__/ _ `// // // __// _ `/ / /|_/ // _ `// __// // _ `/            
/___/ \___//_//_//_/ \__/ \_,_/ /____/\_,_/ \_,_//_/   \_,_/ /_/  /_/ \_,_//_/  /_/ \_,_/            
)" << endl;

  cout << endl;


  cout << "Introduceti utilizatorul: (client/magazin) ";
  getline(cin, utilizator);

  cout << "Introduceti parola: ";
  getline(cin, parola);

  if (utilizator == "client") {
    if (parola != "parolaclient") {
      cout << "Parola incorecta!" << '\n';
      return 1;
    } else meniu = new MeniuClient();
  } else {
    if (parola != "parolamagazin") {
      cout << "Parola incorecta!" << '\n';
      return 1;
    } else meniu = new MeniuMagazin();
  }

  meniu->loop();

  delete meniu;

  DataBase::GetInstance().salveazaDatele();
  return 0;
}
