/// PARTICIPATION GRADE

//  - auto-format in vim with gg=G in normal mode, in vscode with alt+shift+f
//  - gradescript command: python3.11 scripts/test.py airport.cpp

#include <iostream>
#include <vector>

using namespace std;

class Airport {
  private:
    string code;

  public:
    vector<Airport *> connections;
    Airport(const string &acode);
    void addFlight(Airport *airport);
    const string getCode() const;
    bool hasDirect(Airport *airport);
};

class AirportNetwork {
  private:
    vector<Airport *> airports;

  public:
    Airport *findAirport(const string &code);
    void addAirport(const string &code);
    void addConnection(const string &code1, const string &code2);
    void printAirportNetwork();
};

int main() {
    AirportNetwork network;

    network.addAirport("ATL");
    network.addAirport("LAX");
    network.addAirport("JFK");
    network.addAirport("ORD");
    network.addAirport("TYS");
    network.addAirport("BNA");

    network.addConnection("ATL", "LAX");
    network.addConnection("ATL", "JFK");
    network.addConnection("LAX", "ORD");
    network.addConnection("JFK", "ORD");
    network.addConnection("TYS", "ATL");
    network.addConnection("BNA", "JFK");

    network.printAirportNetwork();

    string code1, code2;
    cout << "Enter a 3 character airport code for departure: ";
    cin >> code1;
    cout << "Enter a 3 character airport code for arrival: ";
    cin >> code2;
    Airport *a1 = network.findAirport(code1);
    if (a1 == nullptr) {
        cout << "Invalid airport code." << endl;
        return 1;
    }

    Airport *a2 = network.findAirport(code2);
    if (a2 == nullptr) {
        cout << "Invalid airport code." << endl;
        return 1;
    }

    if (a1->hasDirect(a2))
        cout << "You can fly direct from " << code1 << " to " << code2 << "."
             << endl;
    else
        cout << "You cannot fly direct from " << code1 << " to " << code2 << "."
             << endl;

    return 0;
}

Airport::Airport(const string &acode) { /* TODO */ }

void Airport::addFlight(Airport *airport) { /* TODO */ }

const string Airport::getCode() const { /* TODO */ }

bool Airport::hasDirect(Airport *airport) { /* TODO */ }

Airport *AirportNetwork::findAirport(const string &code) { /* TODO */ }

void AirportNetwork::addAirport(const string &code) { /* TODO */ }

void AirportNetwork::addConnection(const string &code1, const string &code2) {
    /* TODO */
}

void AirportNetwork::printAirportNetwork() { /* TODO */ }
