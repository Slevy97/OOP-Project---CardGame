#include "ThetaEngine.h"
#include <sstream>
#include <string>
#include <iostream>
#include <Windows.h>//temporar
using namespace Theta;

std::string server_name = "oopcardgame.herokuapp.com";

NetworkManager::NetworkManager() {

}

NetworkManager NetworkManager::N_Manager;

int dati = 0;
int dati_high = 0;
int times = 0;
int dati_tura = 0;
extern Table* ptr;
extern std::list<GameObject*> GameObjects;
extern bool myTurn;

void NetworkManager::checkAction()
{
	dati++;
	if (dati > 200) //Aici trebuie sa vedem exact cat putem ca sa vedem cat de rapid il facem
	{
		//std::cout << "Aici da\n";
		if (checkMove())
			getTable();
		/*std::string jm = std::to_string(dati);
		std::wstring stemp = std::wstring(jm.begin(), jm.end());
		LPCWSTR sw = stemp.c_str();
		OutputDebugString(sw);*/
		dati = 0;
	}
}

bool NetworkManager::checkMove()
{
	//std::cout << "Ceva\n";
	sf::Http::Request request("/checkMove", sf::Http::Request::Post);
	sf::Http http(server_name);
	sf::Http::Response response = http.sendRequest(request);
	if (response.getStatus() == sf::Http::Response::Ok)
	{
		if (response.getBody() == "Da")
			return true;
		else
			return false;
	}
	else
	{
		std::cout << "request failed" << std::endl;
		return false;
	}
}

void NetworkManager::acquireplayerID()
{
	sf::Http::Request request("/getID", sf::Http::Request::Post);
	sf::Http http(server_name);
	sf::Http::Response response = http.sendRequest(request);
	if (response.getStatus() == sf::Http::Response::Ok)
	{
		playerID = std::stoi(response.getBody());
		std::cout << playerID;
	}
	else
	{
		/*std::wstring stemp = std::wstring(response.getBody().begin(), response.getBody().end());
		LPCWSTR sw = stemp.c_str();
		OutputDebugString(sw);*/
	}
}

int NetworkManager::getplayerID()
{
	return playerID;
}

void NetworkManager::getTable()
{
	sf::Http::Request request("/getTable", sf::Http::Request::Post);

	sf::Http http(server_name);
	std::ostringstream stream;
	stream << "name=" << playerID;
	request.setBody(stream.str());
	sf::Http::Response response = http.sendRequest(request);
	std::cout << response.getBody() << '\n';
	if (response.getStatus() == sf::Http::Response::Ok)
	{
		std::string s = response.getBody();
		if (s[0] != 'A')
		{
			//Enemy table
			int nr_cards = ptr->enemy_table.getNrCards();
			for (int jj = 0; jj < nr_cards; jj++)
				ptr->enemy_table.erase_card(0);
			int nr = 0;
			int i = 0;
			for (; s[i] != ' '; i++)
			{
				nr = nr * 10 + s[i] - '0';
			}
			i++;
			int contor = 0;
			for (int ii = 0; ii < nr; ii++)
			{
				int id = 0;
				bool negativ = false;
				if (s[i] == '-')
				{
					negativ = true;
					i++;
				}
				for (; s[i] != ' '; i++)
					id = id * 10 + s[i] - '0';
				if (negativ)
					id = -id;
				i++;
				int att = 0;
				negativ = false;
				if (s[i] == '-')
				{
					negativ = true;
					i++;
				}
				for (; s[i] != ' '; i++)
					att = att * 10 + s[i] - '0';
				if (negativ)
					att = -att;
				i++;
				int def = 0;
				negativ = false;
				if (s[i] == '-')
				{
					negativ = true;
					i++;
				}
				for (; s[i] != ' '; i++)
					def = def * 10 + s[i] - '0';
				if (negativ)
					def = -def;
				i++;
				int TurnsToWait = 0;
				negativ = false;
				if (s[i] == '-')
				{
					negativ = true;
					i++;
				}
				for (; s[i] != ' '; i++)
					TurnsToWait = TurnsToWait * 10 + s[i] - '0';
				if (negativ)
					TurnsToWait = -TurnsToWait;
				i++;
				int NrAttacksToMiss = 0;
				negativ = false;
				if (s[i] == '-')
				{
					negativ = true;
					i++;
				}
				for (; s[i] != ' '; i++)
					NrAttacksToMiss = NrAttacksToMiss * 10 + s[i] - '0';
				if (negativ)
					NrAttacksToMiss = -NrAttacksToMiss;
				i++;
				/*if (ptr->enemy_table.getNrCards() > contor)
				{
				if (def <= 0)
				{
				ptr->enemy_table.erase_card(contor);
				contor--;
				}
				else
				{
				ptr->enemy_table.getCard(contor).getCardPtr()->setAttack(att);
				ptr->enemy_table.getCard(contor).getCardPtr()->setDefense(def);
				ptr->enemy_table.getCard(contor).getCardPtr()->setTurnsToWait(TurnsToWait);
				ptr->enemy_table.getCard(contor).getCardPtr()->setNrAttacksToMiss(NrAttacksToMiss);
				}
				}*/
				//else
				//{
				ptr->enemy_table.add_card(id - 1);
				ptr->enemy_table.getCard(ii).getCardPtr()->setAttack(att);
				ptr->enemy_table.getCard(ii).getCardPtr()->setDefense(def);
				ptr->enemy_table.getCard(ii).getCardPtr()->setTurnsToWait(TurnsToWait);
				ptr->enemy_table.getCard(ii).getCardPtr()->setNrAttacksToMiss(NrAttacksToMiss);
				//}
				contor++;
				std::cout << ptr->enemy_table.getNrCards() << " " << contor << " " << def << '\n';
			}

			//Player table
			nr_cards = ptr->player_table.getNrCards();
			for (int jj = 0; jj < nr_cards; jj++)
				ptr->player_table.erase_card(0);
			nr = 0;
			for (; s[i] != ' '; i++)
			{
				nr = nr * 10 + s[i] - '0';
			}
			i++;
			contor = 0;
			for (int ii = 0; ii < nr; ii++)
			{
				int id = 0;
				bool negativ = false;
				if (s[i] == '-')
				{
					negativ = true;
					i++;
				}
				for (; s[i] != ' '; i++)
					id = id * 10 + s[i] - '0';
				if (negativ)
					id = -id;
				i++;
				int att = 0;
				negativ = false;
				if (s[i] == '-')
				{
					negativ = true;
					i++;
				}
				for (; s[i] != ' '; i++)
					att = att * 10 + s[i] - '0';
				if (negativ)
					att = -att;
				i++;
				int def = 0;
				negativ = false;
				if (s[i] == '-')
				{
					negativ = true;
					i++;
				}
				for (; s[i] != ' '; i++)
					def = def * 10 + s[i] - '0';
				if (negativ)
					def = -def;
				i++;
				int TurnsToWait = 0;
				negativ = false;
				if (s[i] == '-')
				{
					negativ = true;
					i++;
				}
				for (; s[i] != ' '; i++)
					TurnsToWait = TurnsToWait * 10 + s[i] - '0';
				if (negativ)
					TurnsToWait = -TurnsToWait;
				i++;
				int NrAttacksToMiss = 0;
				negativ = false;
				if (s[i] == '-')
				{
					negativ = true;
					i++;
				}
				for (; s[i] != ' '; i++)
					NrAttacksToMiss = NrAttacksToMiss * 10 + s[i] - '0';
				if (negativ)
					NrAttacksToMiss = -NrAttacksToMiss;
				i++;
				/*if (ptr->player_table.getNrCards() > contor)
				{
				if (def <= 0)
				{
				ptr->player_table.erase_card(contor);
				contor--;
				}
				else
				{
				ptr->player_table.getCard(contor).getCardPtr()->setAttack(att);
				ptr->player_table.getCard(contor).getCardPtr()->setDefense(def);
				ptr->player_table.getCard(contor).getCardPtr()->setTurnsToWait(TurnsToWait);
				ptr->player_table.getCard(contor).getCardPtr()->setNrAttacksToMiss(NrAttacksToMiss);
				}
				}*/
				//else
				//{
				ptr->player_table.add_card(id - 1);
				ptr->player_table.getCard(ii).getCardPtr()->setAttack(att);
				ptr->player_table.getCard(ii).getCardPtr()->setDefense(def);
				ptr->player_table.getCard(ii).getCardPtr()->setTurnsToWait(TurnsToWait);
				ptr->player_table.getCard(ii).getCardPtr()->setNrAttacksToMiss(NrAttacksToMiss);
				//}
				contor++;
				std::cout << ptr->player_table.getNrCards() << " " << contor << " " << def << '\n';
			}
		}

	}
	else
	{
		/*std::wstring stemp = std::wstring(response.getBody().begin(), response.getBody().end());
		LPCWSTR sw = stemp.c_str();
		OutputDebugString(sw);*/
	}
	std::cout << "Primit\n";

}

/*void NetworkManager::getHighlight()
{
	dati_high++;
	if (dati_high > 200)
	{
		dati_high = 0;
		sf::Http::Request request("/getHighlight", sf::Http::Request::Post);
		sf::Http http(server_name);
		sf::Http::Response response = http.sendRequest(request);
		if (response.getStatus() == sf::Http::Response::Ok)
		{
			if (response.getBody() != "Nu")
			{
				int i = std::stoi(response.getBody());
				std::list<GameObject*>::iterator it;
				for (it = GameObjects.begin(); it != GameObjects.end(); it++)
				{
					Theta::Table* ptr_table = dynamic_cast<Theta::Table*> (*it);
					std::cout << i << '\n';
					//ptr_table->enemy_table.getCard(i).ok_highlight = !ptr_table->enemy_table.getCard(i).ok_highlight;
					//ptr_table->enemy_table.getCard(i).change_attack_state();.
				}
			}
		}
		else
		{
			std::wstring stemp = std::wstring(response.getBody().begin(), response.getBody().end());
			LPCWSTR sw = stemp.c_str();
			OutputDebugString(sw);
		}
	}
}*/

void NetworkManager::getTurnNow()
{
	sf::Http::Request request("/getTurn", sf::Http::Request::Post);
	sf::Http http(server_name);
	std::ostringstream stream;
	stream << "name=" << playerID;
	request.setBody(stream.str());
	sf::Http::Response response = http.sendRequest(request);
	if (response.getBody() == "Da")
	{
		myTurn = true;
		std::cout << "END TURN NOW\n";
	}
}

void NetworkManager::getTurn()
{
	dati_tura++;
	if (dati_tura > 200)
	{
		dati_tura = 0;
		getTurnNow();
		//sendTable();
	}
}

void NetworkManager::restart()
{
	sf::Http::Request request("/restart", sf::Http::Request::Post);
	sf::Http http(server_name);
	sf::Http::Response response = http.sendRequest(request);
}

void NetworkManager::sendTable()
{
	sf::Http::Request request("/sendTable", sf::Http::Request::Post);
	sf::Http http(server_name);
	std::ostringstream stream;
	stream << "name=" << playerID;
	stream << "&table=";
	stream << std::to_string(ptr->player_table.getNrCards()) << " ";
	for (int i = 0; i < ptr->player_table.getNrCards(); i++)
	{
		stream << ptr->player_table.getCard(i).getCardPtr()->getID() << " ";
		stream << ptr->player_table.getCard(i).getCardPtr()->getAttack() << " ";
		stream << ptr->player_table.getCard(i).getCardPtr()->getDefense() << " ";
		stream << ptr->player_table.getCard(i).getCardPtr()->getTurnsToWait() << " ";
		stream << ptr->player_table.getCard(i).getCardPtr()->getNrAttacksToMiss() << " ";
	}
	stream << std::to_string(ptr->enemy_table.getNrCards()) << " ";
	for (int i = 0; i < ptr->enemy_table.getNrCards(); i++)
	{
		stream << ptr->enemy_table.getCard(i).getCardPtr()->getID() << " ";
		stream << ptr->enemy_table.getCard(i).getCardPtr()->getAttack() << " ";
		stream << ptr->enemy_table.getCard(i).getCardPtr()->getDefense() << " ";
		stream << ptr->enemy_table.getCard(i).getCardPtr()->getTurnsToWait() << " ";
		stream << ptr->enemy_table.getCard(i).getCardPtr()->getNrAttacksToMiss() << " ";
	}
	request.setBody(stream.str());
	sf::Http::Response response = http.sendRequest(request);
	std::cout << "trimis\n";
}

/*void NetworkManager::sendHighlight(int index)
{
	sf::Http::Request request("/sendHighlight", sf::Http::Request::Post);
	sf::Http http(server_name);
	std::ostringstream stream;
	stream << "carte=" << std::to_string(index);
	request.setBody(stream.str());
	sf::Http::Response response = http.sendRequest(request);
}*/

void NetworkManager::endTurn()
{
	myTurn = false;
	sf::Http::Request request("/endTurn", sf::Http::Request::Post);
	sf::Http http(server_name);
	std::ostringstream stream;
	stream << "name=" << std::to_string(playerID);
	request.setBody(stream.str());
	sf::Http::Response response = http.sendRequest(request);
	std::cout << "END TURN\n";
}


void NetworkManager::play()
{
	sf::Http::Request request("/play", sf::Http::Request::Post);
	sf::Http http(server_name);
	sf::Http::Response response = http.sendRequest(request);
}

bool NetworkManager::checkStart()
{
	times++;
	if (times > 1000)
	{
		times = 0;
		sf::Http::Request request("/checkStart", sf::Http::Request::Post);

		sf::Http http(server_name);
		sf::Http::Response response = http.sendRequest(request);
		if (response.getStatus() == sf::Http::Response::Ok)
		{
			if (response.getBody() == "Da")
				return true;
			else
				return false;
		}
		else
		{
			std::cout << "request failed" << std::endl;
			return false;
		}
	}
	return false;
}
