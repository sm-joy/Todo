#include "../include/Core.hpp"

const char* DATA_FILE_LOCATION = "tasks.json";

char Core::display_menu()
{
	std::string input{};
	std::cout
		<< "\n        TODO        "
		<< "\n===================="
		<< "\n 1. [A]dd task.     "
		<< "\n 2. [V]iew tasks.   "
		<< "\n 3. [D]elete task.  "
		<< "\n 3. [E]dit status.  "
		<< "\n 4. [Q]uit.         "
		<< "\n===================="
		<< "\n Choose Option ->> ";
	std::getline(std::cin, input);
	
	if (!input.empty()) return input[0];
	else return '\xFF'; //indicator for error;
}

void Core::display_task(TaskList& p_list)
{
	std::cout
		<< "\n     View Mode      "
		<< "\n====================";

	p_list.view_task();

	std::cout 
		<< "\n===================="
		<< "\n Press Enter to exit view mode...";
	std::cin.get();
}

void Core::display_delete_task(TaskList& p_list, json* p_data)
{
	std::cout
		<< "\n    Delete Task     "
		<< "\n====================";
	p_list.view_task();
	std::cout
		<< "\n====================";
	if (p_list.m_tasks.empty())
	{
		std::cout << "\n Press Enter to exit Delete mode...";
		std::cin.get();
		return;
	}
	else
	{
		std::cout << "\n Choose Index ->> ";
		size_t index; std::cin >> index; std::cin.ignore();
		unsigned int id = p_list.delete_task(index - 1);
		if (id == 0)
		{
			Utils::clear_screen();
			Utils::display_error("Invalid index!");
			return;
		}
		else
		{
			delete_task_data(id, p_data);
		}
	}
}

void Core::display_edit_task(TaskList& p_list, json* p_data)
{
	std::cout
		<< "\n    Edit Status     "
		<< "\n====================";
	p_list.view_task();
	std::cout
		<< "\n====================";
	if (p_list.m_tasks.empty())
	{
		std::cout<< "\n Press Enter to exit Edit mode...";
		std::cin.get();
		return;
	}
	else
	{
		std::cout << "\n Choose Index ->> ";

		size_t index{}; std::cin >> index; std::cin.ignore();

		std::cout
			<< "\n    Select Mode     "
			<< "\n===================="
			<< "\n 1. Complete        "
			<< "\n 2. Pending         "
			<< "\n 3. Incomplete      "
			<< "\n===================="
			<< "\n Choose Mode ->> ";

		int mode{}; std::cin >> mode; std::cin.ignore();
		unsigned int id = p_list.set_status(index - 1, mode - 1);
		if (id == 0)
		{
			Utils::clear_screen();
			Utils::display_error("Invalid index or mode!");
			return;
		}
		else
		{
			edit_task_data(id, p_data, static_cast<status_t>(mode-1));
		}
	}
}

json* Core::load_task_data(TaskList& p_list)
{
	json* data = new json;;
	if (Utils::file_exists_t(DATA_FILE_LOCATION))
	{
		std::ifstream rfile(DATA_FILE_LOCATION);
		if (!rfile.is_open())
		{
			Utils::display_error("Error: Cant open the data file");
		}
		else
		{
			rfile >> *data; rfile.close();

			for (const auto& taskdata : (*data)["data"])
			{
				std::string task = taskdata["task"];
				status_t status = static_cast<status_t>(taskdata["status"]);
				std::string time = taskdata["time"];
				unsigned int id = taskdata["id"];
				p_list.m_tasks.emplace_back(task, status, time, id);
			}
		}
	}
	else
	{
		std::ofstream cfile(DATA_FILE_LOCATION);
		if (!cfile.is_open())
		{
			Utils::display_error("Error: File creation failed!");
		}
		cfile.close();
	}

	if (!data->contains("data") || !(*data)["data"].is_array())
	{
		(*data)["data"] = json::array();
	}

	return data;
}

void Core::save_task_data(Task& p_task, json* p_data)
{
	(*p_data)["data"].push_back
	({
		{"id", p_task.m_id},
		{"status", p_task.m_status},
		{"task", p_task.m_task},
		{"time", p_task.m_time}
	});
	
	if (!save_changes(p_data) && !(*p_data)["data"].empty())
	{
		(*p_data)["data"].erase((*p_data)["data"].end() - 1);
	}
}

void Core::edit_task_data(unsigned int p_id, json* p_data, status_t p_status)
{
	for (auto& taskData : (*p_data)["data"])
	{
		if (taskData["id"] == p_id)
		{
			int previous_status = taskData["status"];
			taskData["status"] = static_cast<int>(p_status);
			if (!save_changes(p_data))
			{
				taskData["status"] = previous_status;
			}
			break;
		}
	}
}

void Core::delete_task_data(unsigned int p_id, json* p_data)
{
	for (auto it = ((*p_data)["data"]).begin(); it != ((*p_data)["data"]).end(); ++it)
	{
		if ((*it)["id"] == p_id)
		{
			std::string pretask = (*it)["task"];
			std::string pretime = (*it)["time"];
			unsigned int preid = (*it)["id"];
			int prestatus = (*it)["status"];
			
			(*p_data)["data"].erase(it);

			if (!save_changes(p_data))
			{
				(*p_data)["data"].push_back
				({
					{"id", preid},
					{"status", prestatus},
					{"task", pretask},
					{"time", pretime}
					});
			}
			break;
		}
	}
}

bool Core::save_changes(json* p_data)
{
	std::ofstream wfile(DATA_FILE_LOCATION);
	if (wfile.is_open())
	{
		wfile << p_data->dump(4) << std::endl;
		wfile.close();
	}
	else
	{
		Utils::display_error("Error: Unable to write to file!");
		return false;
	}

	return true;
}
