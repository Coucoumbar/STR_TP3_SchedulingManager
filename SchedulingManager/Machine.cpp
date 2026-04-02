#include "Machine.h"
#include "include/json.hpp"

#include <fstream>
#include <iostream>

Machine::Machine(int id, const string& name) : 
	id(id), 
	name(name) {}

Machine::Machine(int id, const string& name, vector<Device*>& relatedDevices, vector<int>& dependsOn) :
	id(id),
	name(name),
	relatedDevices(relatedDevices),
	dependsOn(dependsOn) {}

unordered_map<int, Machine*> Machine::BuildMachinesFromJsonFile(const string& path, const unordered_map<int, Device*>& devices) {
	unordered_map<int, Machine*> machines;

	using json = nlohmann::json;

	ifstream content(path);
	if (!content) {
		cerr << "Cannot open file: " << path << endl;
		return machines;
	}

	json file = json::parse(content);

	if (!file.contains("machines") || !file["machines"].is_array()) {
		cerr << "JSON does not contain a valid 'machines' array" << endl;
		return machines;
	}

	for (const auto& machine : file["machines"]) {
		int id = machine.at("id").get<int>();
		string name = machine.at("name").get<string>();


		vector<Device*> relatedDevices;
		for (const int device : machine.at("related_devices").get<vector<int>>())
		{
			relatedDevices.push_back(devices.at(device));
		}

		vector<int> dependsOn = machine.at("depends_on").get<vector<int>>();

		machines[id] = new Machine(id, name, relatedDevices, dependsOn);
	}

	return machines;
}