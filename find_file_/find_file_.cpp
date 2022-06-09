
#include "find_file_.h"
#include <thread>

Function_pool::Function_pool() : m_function_queue(), m_lock(), m_data_condition(), m_accept_functions(true)
{
}

Function_pool::~Function_pool()
{
}

void Function_pool::push(std::function<void()> func)
{
    std::unique_lock<std::mutex> lock(m_lock);
    m_function_queue.push(func);
    lock.unlock();
    m_data_condition.notify_one();
}

void Function_pool::done()
{
    std::unique_lock<std::mutex> lock(m_lock);
    m_accept_functions = false;
    lock.unlock();
    m_data_condition.notify_all();

}

void Function_pool::infinite_loop_func()
{
    std::function<void()> func;
    while (true)
    {
        {
            std::unique_lock<std::mutex> lock(m_lock);
            m_data_condition.wait(lock, [this]() {return !m_function_queue.empty() || !m_accept_functions; });
            if (!m_accept_functions && m_function_queue.empty())
            {

                return;
            }
            func = m_function_queue.front();
            m_function_queue.pop();
        }
        func();
    }
}
Function_pool func_pool;

class quit_worker_exception : public std::exception {};
string name_file;
void thead_function()
{
    find_file(name_file);
}

int main(int argc, char* argv[])
{
 

    std::cout << "stating operation" << std::endl;
    int num_threads = 2;
    std::cout << "number of threads = " << num_threads << std::endl;
    std::vector<std::thread> thread_pool;
    for (int i = 0; i < num_threads; i++)
    {
        thread_pool.push_back(std::thread(&Function_pool::infinite_loop_func, &func_pool));
    }
        cout << "Print name of file  ";
        cin >> name_file;
        func_pool.push(thead_function);
    func_pool.done();
    for (unsigned int i = 0; i < thread_pool.size(); i++)
    {
        thread_pool.at(i).join();
    }
}
