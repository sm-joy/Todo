#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>


#include "utils.hpp"

typedef enum TaskStatus
{
	COMPLETE,
	IN_PROGRESS,
	INCOMPLETE
} status_t;



struct Task
{
	std::string m_task;
	status_t m_status;
	std::string m_time;
	unsigned int m_id;

	Task(std::string& p_task, status_t p_status = INCOMPLETE, std::string p_time = "NONE", unsigned int p_id = 0);
	~Task();
};


class TaskList
{

public:
	TaskList();
	~TaskList();
	void add_task(std::string& p_task);
	unsigned int delete_task(size_t p_index);
	void view_task() const;
	//void save_tasks() const;
	//void load_tasks();
	unsigned int set_status(size_t p_index, int p_status);


	std::vector<Task> m_tasks;
};

