#include "Team.h"
#include "include/json.hpp"

#include <fstream>
#include <iostream>

Team::Team(const string& name, const vector<string>& capabilities, int maxCapacity) :
	name(name),
	capabilities(capabilities),
	maxCapacity(maxCapacity) {}

//bool Team::canHandle(const string& deviceType) const {
//
//}

vector<Team*> Team::BuildTeamsFromJsonFile(const string& filename) {
	vector<Team*> teams;

	using json = nlohmann::json;

	ifstream content(filename);
	if (!content) {
		cerr << "Cannot open file: " << filename << endl;
		return teams;
	}

	json file = json::parse(content);

	if (!file.contains("teams") || !file["teams"].is_array()) {
		cerr << "JSON does not contain a valid 'teams' array" << endl;
		return teams;
	}

	for (const auto& team : file["teams"]) {
		string name = team.at("name").get<string>();
		vector<string> capabilities = team.at("capabilities").get<vector<string>>();
		int maxCapacity = team.at("max_capacity").get<int>();

		teams.push_back(new Team(name, capabilities, maxCapacity));
	}

	return teams;
}