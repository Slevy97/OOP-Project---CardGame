#ifndef NETWORK_MANAGER_H_INCLUDED
#define NETWORK_MANAGER_H_INCLUDED
#include "SFML/Network.hpp"

namespace Theta {

	/**	NetworkManager - Singleton that handles the network events
	* that occur in the application.
	**/

	class NetworkManager {

	private:
		static NetworkManager N_Manager;
		NetworkManager();
		NetworkManager(const NetworkManager&) {}
		void operator= (NetworkManager&) {}
		int playerID = 0;
	public:
		~NetworkManager() {}
		static NetworkManager& getHandle() {
			return N_Manager;
		}
		void acquireplayerID(); //gets called only 1 time at the beginnig
		int getplayerID();
		void play(); //lets the server know the player wants to play :)
		bool checkStart(); //sees if the other player connected to the server
		void checkAction(); //handles the networking events
		bool checkMove(); //sees if the other player made a move

		void getTable(); //gets the new table
		//void getHighlight(); //gets the selected card
		void getTurn(); //gets the turn
		void getTurnNow(); //gets the card RIGHT NOW

		void sendTable();  //sends the table
		//void sendHighlight(int); //sends the selected card
		void endTurn(); //ending the turn

		void restart();//restarts the server
	};
}

#endif // !NETWORK_MANAGER_H_INCLUDED