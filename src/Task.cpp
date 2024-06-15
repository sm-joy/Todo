#include "../include/Task.hpp"


Task::Task(std::string& p_task, status_t p_status, std::string p_time, unsigned int p_id)
	:m_task(p_task), m_status(p_status)
{
	if (p_time != "NONE") m_time = p_time;
	else m_time = Utils::current_time();

	if (p_id != 0) m_id = p_id;
	else m_id = Utils::generate_id();
}

Task::~Task()
{}


TaskList::TaskList()
{}

TaskList::~TaskList() 
{}

void TaskList::add_task(std::string& p_task)
{
	m_tasks.emplace_back(p_task);
}

unsigned int TaskList::delete_task(size_t p_index)
{
	if (p_index > m_tasks.size() || p_index < 0) return 0;
	unsigned int id = (m_tasks[p_index]).m_id;
	m_tasks.erase(m_tasks.begin() + p_index); return id;
}

void TaskList::view_task() const
{
	if (m_tasks.empty())
	{
		std::cout << "\nError! No tasks to show yet!";
		return;
	}

	size_t index = 1;
	for (const Task& task : m_tasks)
	{
		std::cout
			<< "\n [" << index << "] "
			<<task.m_task
			<<((task.m_status == COMPLETE) ? " (COMPLETE) " :
			(task.m_status == IN_PROGRESS) ? " (IN PROGRESS) " : " (INCOMPLETE) ")
			<< task.m_time;
		index++;
	}
}

//void TaskList::save_tasks() const
//{
//	if (Utils::file_exists_t(FILE_LOCATION))
//	{
//		std::ofstream file(FILE_LOCATION, std::ios_base::app);
//		if (file.is_open()) {
//			for (const Task& task : m_tasks) 
//			{
//				file << task.m_task << "," << task.m_status << std::endl;
//			}
//			file.close();
//			std::cout << "Tasks appended to file: " << FILE_LOCATION << std::endl;
//		}
//		else 
//		{
//			std::cerr << "Unable to open file: " << FILE_LOCATION << std::endl;
//		}
//	}
//	else
//	{
//		std::ofstream file(FILE_LOCATION);
//		if (file.is_open()) {
//			file << "Task Name,Status" << std::endl;
//			for (const Task& task : m_tasks) 
//			{
//				file << task.m_task << "," << task.m_status << std::endl;
//			}
//			file.close();
//			std::cout << "Tasks saved to file: " << FILE_LOCATION << std::endl;
//		}
//		else 
//		{
//			std::cerr << "Unable to open file: " << FILE_LOCATION << std::endl;
//		}
//	}
//}
//
//void TaskList::load_tasks()
//{
//	std::ifstream file(FILE_LOCATION);
//	if (file.is_open()) 
//	{
//		std::string line;
//		std::getline(file, line);
//		while (std::getline(file, line)) {
//			std::stringstream ss(line);
//			std::string taskName;
//			int status;
//
//			if (std::getline(ss, taskName, ',')) 
//			{
//				ss >> status;
//				m_tasks.emplace_back(taskName, static_cast<status_t>(status));
//			}
//		}
//
//		file.close();
//		std::cout << "Tasks loaded from file: " << FILE_LOCATION << std::endl;
//	}
//	else 
//	{
//		std::cerr << "Unable to open file: " << FILE_LOCATION << std::endl;
//	}
//}

unsigned int TaskList::set_status(size_t p_index, int p_status)
{
	if (p_index > m_tasks.size() || p_index < 0) return 0;
	if (p_status > 2 || p_status < 0) return 0;
	unsigned int id = (m_tasks[p_index]).m_id;
	m_tasks.at(p_index).m_status = static_cast<status_t>(p_status); return id;
}
