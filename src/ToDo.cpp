#include<iostream>

#include "../include/Core.hpp"
#include "../include/Task.hpp"
#include "../include/utils.hpp"

int main()
{
	TaskList list;
	json* taskData = Core::load_task_data(list);

	std::string task{};
	char option{};
	bool run = true;
	while (run)
	{
		Utils::clear_screen();
		char option = Core::display_menu();
		switch (option)
		{

		case 'A':
		case 'a':
			Utils::clear_screen();
			std::cout << "\nEnter Task ->> ";
			std::getline(std::cin, task);
			list.add_task(task);
			Core::save_task_data(list.m_tasks.back(), taskData);
			break;

		case 'V':
		case 'v':
			Utils::clear_screen();
			Core::display_task(list);
			break;

		case 'D':
		case 'd':
			Utils::clear_screen();
			Core::display_delete_task(list, taskData);
			break;

		case 'E':
		case 'e':
			Utils::clear_screen();
			Core::display_edit_task(list,taskData);
			break;

		case 'Q':
		case 'q':
			run = false;
			break;

		case '\xFF':
			Utils::clear_screen();
			Utils::display_error("Empty Input Detected!");
			break;

		default:
			Utils::clear_screen();
			Utils::display_error("Invalid Option!");
			break;
		}
	}

	delete taskData;
	return 0;
}