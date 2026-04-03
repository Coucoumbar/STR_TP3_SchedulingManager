#include "Scheduler.h"

Scheduler::Scheduler(
	const unordered_map<int, Device*>& devices, 
	const unordered_map<int, Machine*>& machines, 
	const vector<Team*>& teams
) :
	devices(devices),
	machines(machines),
	teams(teams) {}