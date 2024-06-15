#pragma once

#include <iostream>
#include <string>
#include "Task.hpp"
#include "utils.hpp"
#include "json.hpp"

using json = nlohmann::json;

namespace Core
{

    char display_menu();
    void display_task(TaskList& p_list);
    void display_delete_task(TaskList& p_list, json* p_data);
    void display_edit_task(TaskList& p_list, json* p_data);
    json* load_task_data(TaskList& p_list); //for all data
    void save_task_data(Task& p_task, json* p_data); // for new data
    void edit_task_data(unsigned int p_id, json* p_data, status_t p_status);
    void delete_task_data(unsigned int p_id, json* p_data);
    bool save_changes(json* p_data); //save json to file
};

