#include "Device.h"
#include "include/json.hpp"

#include <fstream>
#include <iostream>

Device::Device(int id, const string& type, const string& name, int lockTime) : 
	id(id), 
	type(type), 
	name(name), 
	lockTime(lockTime) {}

unordered_map<int, Device*> Device::BuildDevicesFromJsonFile(const string& path) {
	unordered_map<int, Device*> devices;

	using json = nlohmann::json;

	ifstream content(path);
	if (!content) {
		cerr << "Cannot open file: " << path << endl;
		return devices;
	}

	json file = json::parse(content);

	if (!file.contains("devices") || !file["devices"].is_array()) {
		cerr << "JSON does not contain a valid 'devices' array" << endl;
		return devices;
	}

	for (const auto& device : file["devices"]) {
		int id = device.at("id").get<int>();
		string type = device.at("type").get<string>();
		string name = device.at("name").get<string>();
		int lockTime = device.at("lock_time").get<int>();

		devices[id] = new Device(id, type, name, lockTime);
	}

	return devices;
}